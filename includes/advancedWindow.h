#ifndef HEADER_ADVANCEDWINDOW
#define HEADER_ADVANCEDWINDOW

#include <QtGui>



class advancedWindow : public QWidget
{
    Q_OBJECT

	public:
		advancedWindow(QList<bool> selected, QWidget *parent = 0);
		QList<bool> getSelected();
		int getColumns();
	
	public slots:
		void valid();
		void closeEvent(QCloseEvent *);
	
	signals:
		void closed(advancedWindow *);
	
	private:
		QList<bool> selected;
		QList<QCheckBox *> checks;
};

#endif