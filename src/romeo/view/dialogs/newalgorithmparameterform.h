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

namespace Ui {
class NewAlgorithmParameterForm;
}

namespace romeo{
namespace view{
namespace dialogs{

/*!
 * \brief La classe NewAlgorithmParameterForm è un widget che rappresenta un nuovo parametro da inserire.
 *
 * L'utente deve poter inserire il nome del parametro, il tipo del parametro e il valore di default di tale parametro
 */


class NewAlgorithmParameterForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewAlgorithmParameterForm(QWidget *parent = 0);
    ~NewAlgorithmParameterForm();

private:
    Ui::NewAlgorithmParameterForm *ui;
};

}}}
#endif // NEWALGORITHMPARAMETERFORM_H
