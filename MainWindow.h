#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <memory>

#include "NumberConverter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_action_triggered();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_plainTextEdit_textChanged();

	void on_plainTextEdit_2_textChanged();

	void on_action_3_triggered();

private:
	Ui::MainWindow *ui;

	NumberConverter m_conv;

	void keyPressEvent(QKeyEvent *event) override;
	bool eventFilter(QObject *target, QEvent *event) override;
};

#endif // MAINWINDOW_H
