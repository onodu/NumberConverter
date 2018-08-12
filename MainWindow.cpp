#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->plainTextEdit->installEventFilter(this);
	ui->plainTextEdit_2->installEventFilter(this);

	on_pushButton_2_clicked();

	ui->label_7->setText("(" + QString::number(m_conv.minBase()) + ".." + QString::number(m_conv.maxBase()) + ")");
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_action_triggered()
{
	// Exit.
	close();

}

void MainWindow::on_pushButton_clicked()
{
	try
	{
		const std::string inputNumber = ui->plainTextEdit->toPlainText().toStdString();

		const unsigned base1 = std::min(std::max(ui->lineEdit->text().toUInt(), m_conv.minBase()), m_conv.maxBase());
		ui->lineEdit->setText(QString::number(base1));
		const unsigned base2 = std::min(std::max(ui->lineEdit_2->text().toUInt(), m_conv.minBase()), m_conv.maxBase());
		ui->lineEdit_2->setText(QString::number(base2));
		const unsigned digitsAfterPoint = ui->lineEdit_3->text().toUInt();

		std::string res = m_conv(inputNumber, base1, base2, digitsAfterPoint);
		ui->plainTextEdit_2->setPlainText(QString::fromStdString(res));
	}
	catch(NumberConverter::ParserException &ex)
	{
		QMessageBox::critical(this, "Error", ex.what());

		auto cursor = ui->plainTextEdit->textCursor();
		cursor.movePosition(QTextCursor::Start);
		cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, ex.pos());
		ui->plainTextEdit->setTextCursor(cursor);
		ui->plainTextEdit->setFocus();
	}
	catch(std::exception &ex)
	{
		QMessageBox::critical(this, "Error", ex.what());
	}
}

void MainWindow::on_pushButton_2_clicked()
{
	ui->plainTextEdit->setPlainText("");
	ui->lineEdit->setText("10");
	ui->lineEdit_2->setText("2");
	ui->lineEdit_3->setText("0");
	ui->plainTextEdit_2->setPlainText("");
	ui->plainTextEdit->setFocus();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
	case Qt::Key_Return :
	case Qt::Key_Enter :
		on_pushButton_clicked();
		break;

	case Qt::Key_Escape :
		on_pushButton_2_clicked();
		break;
	}
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
	if(target == ui->plainTextEdit || target == ui->plainTextEdit_2)
	{
		if(event->type() == QEvent::KeyPress)
		{
			const QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
			{
				on_pushButton_clicked();
				return true;
			}
			if(keyEvent->key() == Qt::Key_Escape)
			{
				on_pushButton_2_clicked();
				return true;
			}
		}
	}
	return QMainWindow::eventFilter(target, event);
}


void MainWindow::on_plainTextEdit_textChanged()
{
	ui->label_5->setText(QString::number(ui->plainTextEdit->toPlainText().size()));
}

void MainWindow::on_plainTextEdit_2_textChanged()
{
	ui->label_6->setText(QString::number(ui->plainTextEdit_2->toPlainText().size()));
}

void MainWindow::on_action_3_triggered()
{
	QMessageBox::information(this, "Grammar", R"(E -> [0-9a-zA-Z]*(\.[0-9a-zA-Z]*)?)");

}
