#ifndef CDIALOGPLUGINSMANAGER_H
#define CDIALOGPLUGINSMANAGER_H

#include <QDialog>

class QHBoxLayout;
class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;

class CGBPluginDetails;


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
    void    _initialize_twList(void);

    void        listPopulate(void);

    QStringList listActivatedPlugins(void) const;

    QString     currentlySelectedPluginId(void) const;


    Q_SLOT  virtual void    accept();
    Q_SLOT  void            on_m_twList_currentItemChanged( QTreeWidgetItem*,
                                                            QTreeWidgetItem* );



public:
protected:
private:

    struct  Column
    {
        enum    EColumnsIndex
        {
            Name        = 0,
            Version,
            Activated,
            ID,

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


    CGBPluginDetails*   m_gbPluginDetails;
    QPushButton*        m_pbAccept;
    QPushButton*        m_pbCancel;
    QTreeWidget*        m_twList;



};

#endif  /*< CDIALOGPLUGINSMANAGER_H */
