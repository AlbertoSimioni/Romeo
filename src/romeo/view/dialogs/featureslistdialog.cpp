#include "featureslistdialog.h"
#include "ui_featureslistdialog.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::features;
FeaturesListDialog::FeaturesListDialog(FeaturesList *feats, QWidget *parent) :
    QDialog(parent), features(feats),
    ui(new Ui::FeaturesListDialog)
{
    ui->setupUi(this);
    connectUI();
    fillFeaturesList();
}

FeaturesListDialog::~FeaturesListDialog()
{
    delete ui;
}


void FeaturesListDialog::connectUI(){
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(features,SIGNAL(featuresListModified()),this,SLOT(fillFeaturesList()));
    connect(ui->featureTable,SIGNAL(clicked(QModelIndex)),this,SLOT(showDescription()));
}


void FeaturesListDialog::fillFeaturesList(){
    ui->featureTable->clear();
    ui->descriptionText->clear();

    QList<AbstractFeature*> feats =features->getFeaturesList();

    for(int i = 0; i< feats.size();i++){
        ui->featureTable->addItem(feats[i]->getName());
    }

}

void FeaturesListDialog::showDescription(){

    QList<QListWidgetItem*> selected =  ui->featureTable->selectedItems();
    if(!selected.isEmpty()){
        QString featName =  selected.at(0)->text();
        AbstractFeature* feature =features->getFeature(featName);
        ui->descriptionText->setText(feature->getDescription());
    }


}
