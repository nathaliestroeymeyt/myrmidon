#pragma once

#include <QWidget>

namespace Ui {
class UserDataWidget;
}

class AntMetadataBridge;

class UserDataWidget : public QWidget {
	Q_OBJECT
public:
	explicit UserDataWidget(QWidget *parent = 0);
	~UserDataWidget();

	void setup(AntMetadataBridge * metadata);

private slots:
	void on_tableView_activated(const QModelIndex & index);

private:
	Ui::UserDataWidget * d_ui;
	AntMetadataBridge  * d_metadata;
};
