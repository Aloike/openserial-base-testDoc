#ifndef CGBPLUGINDETAILS_H
#define CGBPLUGINDETAILS_H

#include <QGroupBox>

class QLabel;


class   CGBPluginDetails
        :   public  QGroupBox
{

public:

    CGBPluginDetails(QWidget *argParent);

    void    clear(void);
    void    setDisplayedPlugin( const QString& argPluginId );



protected:
private:



public:
protected:
private:

    QLabel* m_lDescription;
    QLabel* m_lEditorName;
    QLabel* m_lName;
    QLabel* m_lPath;
    QLabel* m_lVersion;



};

#endif  /*< CGBPLUGINDETAILS_H */
