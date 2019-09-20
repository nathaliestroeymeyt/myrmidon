#pragma once

#include <QWidget>

#include "Experiment.hpp"


namespace Ui {
class ExperimentInfoWidget;
}

class ExperimentInfoWidget : public QWidget {
	Q_OBJECT
public:
	explicit ExperimentInfoWidget(QWidget *parent = nullptr);
	~ExperimentInfoWidget();

	void setExperiment(Experiment * exp);

signals:
	void addTriggered();
	void deleteTriggered(const QString & path);

public slots:
	void onExperimentPathModified(const QString & path);
	void on_addButton_triggered();
	void on_removeButton_triggered();


private:
	Ui::ExperimentInfoWidget * d_ui;
	Experiment               * d_experiment;
};
