#pragma once

#include <QObject>

class Stage  : public QObject
{
	Q_OBJECT

public:
	QString name;
	QString description;
	QString* caseInput, * caseOutput;
	int chapter=0, id=0;
	void setInfo(QString n, QString d, int c, int i)
	{
		name = n;
		description = d;
		chapter = c;
		id = i;
	}
	Stage(QObject *parent);
	~Stage();
};
