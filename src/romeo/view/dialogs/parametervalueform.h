/**
* \file parametervalueform.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ParameterValueForm del package romeo::view::dialogs
*/

#ifndef PARAMETERVALUEFORM_H
#define PARAMETERVALUEFORM_H

#include <QWidget>
#include <src/romeo/model/protocols/abstractprotocol.h>
namespace Ui {
class ParameterValueForm;
}


namespace romeo{
namespace view{
namespace dialogs{

/*!
 * \brief La classe ParameterValueForm è un widget che rappresenta un generico parametro da inserire
 *
 * è composta da una linea di testo che identifica il nome del parametro, una linea di testo modificabile in cui è possibile inserire il valore del parametro
 * e una linea di testo che indica il tipo del parametro
 */
class ParameterValueForm : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterValueForm( romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter parameter, QWidget *parent = 0);
    ~ParameterValueForm();
    /*!
     * \brief Ritorna il nome del parametro
     */
    QString getName();
    /*!
     * \brief Ritorna il valore inserito dall'utente nella linea di testo
     */
    QString getValue();
    /*!
     * \brief Ritorna il tipo del parametro
     */
    romeo::model::protocols::algorithms::AbstractAlgorithm::ParameterType getType();
    /*!
     * \brief Ritorna l'intero parametro.
     */
    romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter getParameter();

    /*!
     * \brief Ritorna true se il valore del parametro è valido rispetto al suo tipo
     */
    bool isValid() const;


signals:
    /*!
     * \brief Segnale emesso quando l'utente modifica il valore del parametro
     * \param valid indica se il valore inserito è valido o meno rispetto al tipo del parametro
     */
    void valueEntered(bool valid);

private slots:
    /*!
     * \brief Viene avviato quando l'utente modifica il valore inserito.
     *
     * Segnala la validità del parametro tramite il segnale valueEntered(bool)
     */
    void checkValidity(QString value);

private:
    Ui::ParameterValueForm *ui;
    /*!
     * \brief Tipo del parametro, campo dati necessario per poter fare dei controlli sul valore del parametro inserito dall'utente
     */
    romeo::model::protocols::algorithms::AbstractAlgorithm::ParameterType type;

    /*!
     * \brief Indica se il valore del parametro è valido rispetto al suo tipo.
     */
    bool validValue;
};

}}}
#endif // PARAMETERVALUEFORM_H
