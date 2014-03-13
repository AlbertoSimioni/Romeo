/**
* \file explorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe Explorer del package romeo::view::mainWindow
*/

#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include "datasetsexplorer.h"
#include "protocolsexplorer.h"

namespace Ui {
class Explorer;
}
namespace romeo {
namespace view {
namespace mainWindow{

/*!
 * \brief The Explorer class
 */
class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();
    /*!
     * \brief Ritorna il riferimento al widget che mostra la lista dei dataset
     */
    DatasetsExplorer* getDatasetsExplorer();
    /*!
     * \brief Ritorna il riferimento al widget che mostra la lista dei protocolli
     */
    ProtocolsExplorer* getProtocolsExplorer();

private:
    Ui::Explorer *ui;
};
}}}

#endif // EXPLORER_H
