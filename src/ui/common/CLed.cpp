#include "CLed.h"

#include <QPainter>
#include <QRadialGradient>
#include <QRect>



/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Default constructor.
 *
 *  @param  parent  The parent widget.
 */
CLed::CLed(QWidget *parent)
    :   QWidget(parent)
    ,   m_colorCurrent(Qt::gray)
    ,   m_colorStateActivated(Qt::red)
    ,   m_colorStateDeactivated(Qt::gray)
    ,   m_isActivated(false)
{
    this->setMinimumWidth( 10 );
    this->setMinimumHeight( 10 );

    this->resize( 25, 25 );

//    this->m_colorStateDeactivated= QColor( 100,100,100 );

    this->setActivated(false);
    this->repaint();
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Constructor.
 *
 *  @param  argMinWidth     The minimum led's width.
 *  @param  argMinHeight    The minimum led's height.
 *  @param  parent          The parent widget.
 */
CLed::CLed(const int argMinWidth, const int argMinHeight, QWidget *parent)
    :   QWidget(parent)
    ,   m_colorCurrent(m_colorStateDeactivated)
    ,   m_colorStateActivated(Qt::red)
    ,   m_colorStateDeactivated(Qt::gray)
    ,   m_isActivated(false)
{
    this->setMinimumWidth(argMinWidth);
    this->setMinimumHeight(argMinHeight);

//    this->m_colorStateDeactivated.setRgb(100,100,100);

    this->setActivated(false);
    this->repaint();
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  The color the LED takes when activated.
 *
 *  @return A const reference to the LED's QColor.
 */
const QColor&   CLed::color(void) const
{
    return this->m_colorStateActivated;
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Returns the current state of the LED.
 *
 *  @retval true    If the LED is activated;
 *  @retval false   otherwise.
 */
bool    CLed::isActivated(void) const
{
    return this->m_isActivated;
}

/* ########################################################################## */
/* ########################################################################## */

void CLed::paintEvent(QPaintEvent *)
{
    QPainter    lPainter;
    QColor      lColor  = this->m_colorStateDeactivated;


    lPainter.begin(this);
    lPainter.setRenderHint(QPainter::Antialiasing);


    /* Select the current color depending on the current state */
    if( this->isActivated() )
    {
        lColor  = this->color();
    }


    /* Calculate the position */
    int side = (this->width() < this->height()? this->width():this->height());
    int posX = (this->width()/2)-(side/2);
    int posY = (this->height()/2)-(side/2);
    QRect contour(posX,posY,side, side);

    /* Draw the contour */
    lPainter.setPen(Qt::black);
    lPainter.setBrush(lColor);
    lPainter.drawEllipse(contour);

    /* Draw the gradient to make it more realistic */
    QRadialGradient gradient(posX + (side/1.65), posY + (side/2.5), side/2 );
    gradient.setColorAt(0.0, (this->isActivated() ? Qt::white : Qt::lightGray));
    gradient.setColorAt((this->isActivated()? 0.7 : 0.4), lColor);
    gradient.setColorAt(1.0, Qt::transparent);

    lPainter.setBrush(gradient);
    lPainter.drawEllipse(contour);
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief   Sets the LED's current state.
 *
 *  @param argState  The LED's state
 */
void CLed::setActivated(const bool &argState)
{
    this->m_isActivated = argState;
    this->repaint();
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Defines the color the LED takes when activated.
 *
 *  @param  argColor  The led's color.
 */
void CLed::setColor(const QColor &argColor)
{
    this->m_colorStateActivated = argColor;
    this->repaint();
}

/* ########################################################################## */
/* ########################################################################## */
