#ifndef  GQTBUTTONSWIDGET_H
#define  GQTBUTTONSWIDGET_H  1

// c++
#include <string>
#include <vector>

// qt
#include <QtWidgets>

struct ButtonInfo
{
	// a button name must have 2 png files:
	// 1. "name_1.png"
	// 2. "name_2.png"
	ButtonInfo(std::string icon);

public:
	QListWidgetItem *thisButton;
	QIcon buttonForState(int state);

private:
	std::string buttonName;
};



class  GQTButtonsWidget : public QWidget
{
	Q_OBJECT

public:
	GQTButtonsWidget(double h, double v, std::vector<std::string> bicons, QWidget *parent = Q_NULLPTR);

	~GQTButtonsWidget() {
		delete buttonsWidget;
		for ( auto* button: buttons )  { delete button; }
	}

private:
	QListWidget *buttonsWidget;

	std::vector<ButtonInfo*> buttons;

	private slots:
	void buttonWasPressed(QListWidgetItem*);


};


#endif
