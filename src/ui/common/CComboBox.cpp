#include "CComboBox.h"

#include <QLineEdit>


/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Constructor of the CComboBox class.
 *
 *  @param  argParent   Pointer to the parent widget.
 */
CComboBox::CComboBox(QWidget *argParent, bool argIsEditable)
    :   QComboBox( argParent )
    ,   m_alignment( Qt::AlignLeft | Qt::AlignVCenter )
{
    this->setEditable(true);
    this->lineEdit()->setDisabled(false);
    this->lineEdit()->setReadOnly( ! argIsEditable );
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief Destructor of the CComboBox class.
 */
CComboBox::~CComboBox()
{
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::addItem( const QString   &argText,
                            const QVariant  &argUserData )
{
    this->insertItem(count(), argText, argUserData);
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::addItem( const QIcon     &argIcon,
                            const QString   &argText,
                            const QVariant  &argUserData )
{
    this->insertItem(count(), argIcon, argText, argUserData);
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::addItems(const QStringList &argTexts)
{
    this->insertItems(count(), argTexts);
}

/* ########################################################################## */
/* ########################################################################## */

Qt::Alignment   CComboBox::alignment() const
{
    return this->m_alignment;
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::insertItem( int              aindex,
                               const QString    &atext,
                               const QVariant   &auserData )
{
    QComboBox::insertItem(aindex, QIcon(), atext, auserData);
    this->setAlignment( this->alignment() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::insertItem( int              index,
                               const QIcon      &icon,
                               const QString    &text,
                               const QVariant   &userData )
{
    QComboBox::insertItem( index, icon, text, userData );
    this->setAlignment( this->alignment() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::insertItems( int                 argIndex,
                                const QStringList   &argTexts )
{
    QComboBox::insertItems( argIndex, argTexts );
    this->setAlignment( this->alignment() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::mousePressEvent(QMouseEvent *e)
{
    QComboBox::mousePressEvent( e );
    if( this->lineEdit()->isReadOnly() )
    {
        this->showPopup();
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::setAlignment(Qt::Alignment argAlign)
{
    this->m_alignment   = argAlign;

    this->lineEdit()->setAlignment( this->alignment() );

    for (int i = 0 ; i < this->count() ; ++i)
    {
        this->setItemData( i,
                           QVariant(this->alignment()),
                           Qt::TextAlignmentRole );
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CComboBox::setEditable(bool argIsEditable)
{
    QComboBox::setEditable( argIsEditable );
    this->lineEdit()->setReadOnly( ! argIsEditable );
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  This method overloads QComboBox::showPopup() to be able to emit a
 *          signal when the drop-list is about to show.
 *
 * Having the \ref aboutToShowPopup signal available is convenient to update the
 * list before it is shown to the operator.
 */
void    CComboBox::showPopup()
{
    emit this->aboutToShowPopup();
    QComboBox::showPopup();
}

/* ########################################################################## */
/* ########################################################################## */
