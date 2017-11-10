#ifndef CLED_H
#define CLED_H

/*!
 * \file CLed.h
 * \brief Objet représentant un diode electro-luminescente
 * \author MGO
 * \version 1.0
 */

#include <QColor>
#include <QWidget>


/*! \class  CLed
   * \brief Classe représentant une DEL.
   *
   * Cette classe est un widget sur lequel est dessiné une diode
   * electro-luminescente.
   */
class CLed : public QWidget
{

    Q_OBJECT

public:

    /* Macros to have the properties available in QtDesigner */
    Q_PROPERTY(bool Activated READ isActivated WRITE setActivated)
    Q_PROPERTY(QColor ColorWhenActivated READ color WRITE setColor)


    explicit CLed(QWidget *parent = 0);
    explicit CLed(const int argMinWidth, const int argMinHeight,
                  QWidget *parent = 0);


    const QColor&   color(void) const;
    void            setColor(const QColor &argColor);

    bool            isActivated(void) const;
    void            setActivated(const bool &argState);



protected:

    void paintEvent(QPaintEvent *);



private:



public slots:
protected slots:
private slots:



public:
protected:
private:

    QColor  m_colorCurrent;
    QColor  m_colorStateActivated;
    QColor  m_colorStateDeactivated;
    bool    m_isActivated;



signals:



};

#endif /*< CLED_H */
