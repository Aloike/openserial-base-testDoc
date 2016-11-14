#ifndef CPORTSCOMBOBOX_H
#define CPORTSCOMBOBOX_H

#include <QComboBox>


class CComboBox : public QComboBox
{
    Q_OBJECT

public:

    explicit CComboBox(QWidget *argParent = 0, bool argIsEditable=false);
    virtual ~CComboBox();


    virtual void showPopup();


    Qt::Alignment   alignment(void) const;
    void            setAlignment(Qt::Alignment argAlign);


    void    addItem( const QString  &atext,
                     const QVariant &auserData=QVariant() );

    void    addItem( const QIcon    &aicon,
                     const QString  &atext,
                     const QVariant &auserData );

    void    addItems( const QStringList &texts );


    void    insertItem( int             index,
                        const QString   &text,
                        const QVariant  &userData );

    void    insertItem( int             index,
                        const QIcon     &icon,
                        const QString   &text,
                        const QVariant  &userData = QVariant() );

    void    insertItems( int                index,
                         const QStringList  &texts );



protected:

    void    mousePressEvent(QMouseEvent *e);

    void    setEditable(bool editable);



private:



public slots:
protected slots:
private slots:



public:
protected:
private:

    Qt::Alignment   m_alignment;



signals:

    void    aboutToShowPopup(void);



};

#endif /*< CPORTSCOMBOBOX_H */
