#ifndef CDIALOGPLUGINSMANAGER_H
#define CDIALOGPLUGINSMANAGER_H

#include <QDialog>

class QHBoxLayout;
class QPushButton;
class QTableWidget;


class   CDialogPluginsManager
        :   public  QDialog
{
    Q_OBJECT

public:

    explicit CDialogPluginsManager(QWidget *argParentPtr = 0);



protected:
private:

    void    _create_ui_layout(void);
    void    _create_connections(void);

    void        listPopulate(void);

    QStringList listActivatedPlugins(void) const;



    Q_SLOT  virtual void    accept();
    Q_SLOT  void            on_m_twList_currentCellChanged(int,int,int,int);



public:
protected:
private:

    struct  Column
    {
        enum    EColumnsIndex
        {
            Activated   = 0,
            ID,
            Name,
            Version,
            Description,
            Path,

            ColumnsCount
        };
    };


    QPushButton*    m_pbAccept;
    QPushButton*    m_pbCancel;
    QTableWidget*   m_twList;



};

#endif  /*< CDIALOGPLUGINSMANAGER_H */
