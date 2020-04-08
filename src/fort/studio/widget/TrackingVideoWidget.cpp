#include "TrackingVideoWidget.hpp"
#include "TrackingVideoFrame.hpp"


#include <fort/studio/Format.hpp>

#include <fort/studio/bridge/IdentifierBridge.hpp>


#include <QPainter>



TrackingVideoWidget::TrackingVideoWidget(QWidget * parent)
	: QWidget(parent)
	, d_image(0,0)
	, d_identifier(nullptr)
	, d_hideLoadingBanner(true) {
}

TrackingVideoWidget::~TrackingVideoWidget() {
}


void TrackingVideoWidget::display(TrackingVideoFrame frame) {
	VIDEO_PLAYER_DEBUG(std::cerr << "Received frame:" << frame << std::endl);
	if ( !frame.Image ) {
		d_image = QImage(0,0);
		update();
		return;
	}
	d_image = *frame.Image;
	QPainter painter(&d_image);
	painter.setRenderHint(QPainter::Antialiasing,true);
	if ( !frame.TrackingFrame == false || d_identifier == nullptr ) {
		paintIdentifiedAnt(&painter,frame.TrackingFrame,frame.Image->height());
	}
	update();
}

void TrackingVideoWidget::paintEvent(QPaintEvent * event) {
	QPainter painter(this);
	painter.fillRect(rect(),QColor(0,0,0));
	if ( d_image.isNull() == true ) {
		return;
	}

	auto size = d_image.size();
	size.scale(width(),height(),Qt::KeepAspectRatio);
	QRect targetRect(QPoint(0,0),size);
	targetRect.translate(rect().center()-targetRect.center());

	painter.drawImage(targetRect,d_image);

	if ( d_hideLoadingBanner == false ) {
		auto font = painter.font();
		font.setPointSize(14);
		painter.setFont(font);
		painter.setBrush(QColor(255,255,255,150));
		painter.setPen(Qt::NoPen);
		auto rect = QRectF(0,0,width(),60);

		painter.drawRect(rect);

		painter.setPen(QColor(0,0,0));
		painter.drawText(rect,
		                 Qt::AlignCenter,
		                 tr("Tracking Data Loading (available displayed, but seek disabled)"));
	}
}

void TrackingVideoWidget::setup(IdentifierBridge *identifier) {
	d_identifier = identifier;
}



void TrackingVideoWidget::paintIdentifiedAnt(QPainter * painter,
                                             const fmp::IdentifiedFrame::ConstPtr & frame,
                                             int targetHeight) {
	double ratio = double(targetHeight) / double(frame->Height);
	const static double ANT_HALF_SIZE = 10.0;

	painter->setPen(Qt::NoPen);

	bool hasSolo = d_identifier->numberSoloAnt() != 0;
	for ( const auto & pa : frame->Positions ) {
		auto a = d_identifier->ant(pa.ID);
		if ( !a
		     || ( hasSolo == true && a->DisplayStatus() != fmp::Ant::DisplayState::SOLO)
		     || a->DisplayStatus() == fmp::Ant::DisplayState::HIDDEN ) {
			continue;
		}
		auto c = Conversion::colorFromFM(a->DisplayColor(),150);
		painter->setBrush(c);
		painter->drawEllipse(QRectF(ratio * pa.Position.x() - ANT_HALF_SIZE,
		                            ratio * pa.Position.y() - ANT_HALF_SIZE,
		                            ANT_HALF_SIZE * 2.0,
		                            ANT_HALF_SIZE * 2.0));
	}

}

void TrackingVideoWidget::hideLoadingBanner(bool hide) {
	if ( hide == d_hideLoadingBanner ) {
		return;
	}
	d_hideLoadingBanner = hide;
	update();
}