#pragma once

#include "Workspace.hpp"

namespace Ui {
class GeneralWorkspace;
}

class GeneralWorkspace : public Workspace {
	Q_OBJECT
public:
	explicit GeneralWorkspace(QWidget *parent = 0);
	virtual ~GeneralWorkspace();

protected:
	void initialize(QMainWindow * main,ExperimentBridge * experiment) override;
	void setUp(const NavigationAction & actions) override;
	void tearDown(const NavigationAction & actions) override;


private:
	Ui::GeneralWorkspace * d_ui;
};
