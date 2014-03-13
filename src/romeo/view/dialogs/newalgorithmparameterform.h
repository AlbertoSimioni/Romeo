/**
* \file newalgorithmparameterform.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewAlgorithmParameterForm del package romeo::view::dialogs
*/


#ifndef NEWALGORITHMPARAMETERFORM_H
#define NEWALGORITHMPARAMETERFORM_H
#include <QWidget>
#include "src/romeo/model/protocols/algorithms/abstractalgorithm.h"
namespace Ui {
class NewAlgorithmParameterForm;
}

namespace romeo{
namespace view{
namespace dialogs{

/*!
 * \brief La classe NewAlgorithmParameterForm è un widget che rappresenta un nuovo parametro da inserire.
 *
 * L'utente deve poter inserire il nome del parametro, il tipo del parametro e il valore di default di tale parametro.
 */


class NewAlgorithmParameterForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewAlgorithmParameterForm(QWidget *parent = 0);
    ~NewAlgorithmParameterForm();

    /*!
     * \brief Ritorna true se il valore del parametro è valido rispetto al suo tipo
     */
    bool isValid();

    /*!
     * \brief Ritorna il nome del parametro inserito dall'utente
     */
    QString getName();

    /*!
     * \brief Ritorna il tipo del parametro inserito dall'utente
     */
    romeo::model::protocols::algorithms::AbstractAlgorithm::ParameterType getType();

    /*!
     * \brief Ritorna il valore di defult inserito dall'utente come stringa
     */
    QString getDefault();



signals:
    /*!
     * \brief Segnale emesso quando l'utente modifica il valore del parametro
     */
    void valueEntered();

    /*!
     * \brief Segnale emesso quando l'utente preme il pulsante per cancellare il parametro
     */
    void deletePressed(NewAlgorithmParameterForm* param);


private slots:
    /*!
     * \brief Slot avviato quando l'utente modifica un qualche campo della form, controlla la validità dei dati inseriti
     */
    void checkValidity();

    /*!
     * \brief Slot avviato quando viene premuto il pulsante per la cancellazione del parametro.
     *
     * Si preoccupa di emettere il signale deletePressed passando il this come parametro
     */
    void onDeleteClicked();
private:


    Ui::NewAlgorithmParameterForm *ui;

    /*!
     * \brief Campo dati che indica se i dati inseriti dall'utente sono validi
     */
    bool valid;

};

}}}
#endif // NEWALGORITHMPARAMETERFORM_H
