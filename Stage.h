#pragma once

#include <QObject>

class Stage  : public QObject
{
	Q_OBJECT

public:
	QString name;
	QString description;
	QString* caseInput, * caseOutput;

	Stage(QObject *parent);
	~Stage();
};
