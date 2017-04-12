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
            ID          = 0,
            Activated,
            Name,
            Version,

            _ColumnsCount
        };

        static int  count(void)
        {
            return _ColumnsCount;
        }

        static QStringList  names(void)
        {
            QStringList retVal;


            for( int i = 0 ; i < Column::count() ; ++i )
            {
                switch( i )
                {
                    case    Column::Activated:
                        retVal.append( tr( "Activated" ) );
                        break;

                    case    Column::ID:
                        retVal.append( tr( "ID" ) );
                        break;

                    case    Column::Name:
                        retVal.append( tr( "Name" ) );
                        break;

                    case    Column::Version:
                        retVal.append( tr( "Version" ) );
                        break;

                    default:
                        retVal.append( tr( "[[Unknown column name]]" ) );
                        break;
                }
            }

            return retVal;
        }
    };


    QPushButton*    m_pbAccept;
    QPushButton*    m_pbCancel;
    QTableWidget*   m_twList;



};

#endif  /*< CDIALOGPLUGINSMANAGER_H */
