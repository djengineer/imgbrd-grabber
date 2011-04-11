#include "addgroupwindow.h"

AddGroupWindow::AddGroupWindow(QMap<QString,int> favorites, mainWindow *parent) : QWidget(parent), m_parent(parent)
{
	QVBoxLayout *layout = new QVBoxLayout;
		QFormLayout *formLayout = new QFormLayout;
			m_lineTags = new TextEdit(favorites, this);
				m_lineTags->setContextMenuPolicy(Qt::CustomContextMenu);
				QStringList completion;
					QFile words("words.txt");
					if (words.open(QIODevice::ReadOnly | QIODevice::Text))
					{
						while (!words.atEnd())
						{
							QByteArray line = words.readLine();
							completion.append(QString(line).remove("\r\n").remove("\n").split(" ", QString::SkipEmptyParts));
						}
						QCompleter *completer = new QCompleter(completion, this);
						completer->setCaseSensitivity(Qt::CaseInsensitive);
						m_lineTags->setCompleter(completer);
					}
				formLayout->addRow(tr("&Tags"), m_lineTags);
			m_spinPage = new QSpinBox;
				m_spinPage->setRange(1, 1000);
				m_spinPage->setValue(1);
				formLayout->addRow(tr("&Page"), m_spinPage);
			m_spinPP = new QSpinBox;
				m_spinPP->setRange(1, 100);
				m_spinPP->setValue(100);
				formLayout->addRow(tr("&Images par page"), m_spinPP);
			m_spinLimit = new QSpinBox;
				m_spinLimit->setRange(1, 1000000);
				m_spinLimit->setValue(100);
				formLayout->addRow(tr("&Limite d'images"), m_spinLimit);
			m_comboDwl = new QComboBox;
				m_comboDwl->setMaxVisibleItems(20);
				m_comboDwl->addItems(QStringList() << tr("Oui") << tr("Non"));
				m_comboDwl->setCurrentIndex(1);
				formLayout->addRow(tr("&T�l�charger les image de la liste noire"), m_comboDwl);
			layout->addLayout(formLayout);
		QHBoxLayout *layoutButtons = new QHBoxLayout;
			QPushButton *buttonOk = new QPushButton(tr("Ok"));
				connect(buttonOk, SIGNAL(clicked()), this, SLOT(ok()));
				layoutButtons->addWidget(buttonOk);
			QPushButton *buttonClose = new QPushButton(tr("Fermer"));
				connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));
				layoutButtons->addWidget(buttonClose);
			layout->addLayout(layoutButtons);
	this->setLayout(layout);
	this->setWindowIcon(QIcon(":/images/icon.ico"));
	this->setWindowTitle(tr("Grabber")+" - "+tr("Ajouter groupe"));
	this->setWindowFlags(Qt::Window);
	this->resize(QSize(400, 0));
}

void AddGroupWindow::ok()
{
	QStringList bools = QStringList() << "true" << "false";
	QStringList values = QStringList() << m_lineTags->toPlainText() << QString::number(m_spinPage->value()) << QString::number(m_spinPP->value()) << QString::number(m_spinLimit->value()) << bools.at(m_comboDwl->currentIndex()) << "danbooru.donmai.us" << "";
	m_parent->batchAddGroup(values);
	this->close();
}