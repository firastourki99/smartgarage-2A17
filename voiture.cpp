#include "voiture.h"

Voiture::Voiture()
{

}

Voiture::Voiture(int matricule, int cin, QString marque, QString modele, QString couleur, QDate date)
{
    this->matricule = matricule;
    this->cin = cin;
    this->marque = marque;
    this->modele = modele;
    this->couleur = couleur;
    this->date = date;
}

int Voiture::getIdClient(){return cin;}
int Voiture::getMatricule(){return matricule;}
QString Voiture::getMarque(){return marque;}
QString Voiture::getModele(){return modele;}
QString Voiture::getCouleur(){return couleur;}
QDate Voiture::getDate(){return date;}


void Voiture::setIdClient(int id){this->cin = id;}
void Voiture::setMatricule(int matricule){this->matricule = matricule;}
void Voiture::setMarque(QString marque){this->marque = marque;}
void Voiture::setModele(QString modele){this->modele = modele;}
void Voiture::setCouleur(QString couleur){this->couleur = couleur;}
void Voiture::setDate(QDate date){this->date = date;}

bool Voiture::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(cin);
    QString id_matricule = QString::number(matricule);
          query.prepare("INSERT INTO voiture (matricule, CIN, marque, modele, couleur, DATE_AJOUT) "
                        "VALUES (:matricule, :IdClient, :marque, :modele, :couleur, :date)");
          query.bindValue(":IdClient", id_string);
          query.bindValue(":matricule", id_matricule);
          query.bindValue(":marque", marque);
          query.bindValue(":modele", modele);
          query.bindValue(":couleur", couleur);
          query.bindValue(":date", date);

    return query.exec();
}

QSqlQueryModel * Voiture::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from Voiture");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modele"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Couleur"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));

    return model;
}

bool Voiture::suprimmer(int mat)
{
    QSqlQuery query;
          query.prepare("DELETE FROM voiture where MATRICULE =: mat");
          query.bindValue(0, mat);

    return query.exec();
}

bool Voiture::modifier(int &row, QString &s, QString &val)
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(row));
    msgBox.setText(s);
    msgBox.setText(val);
    QSqlQuery query;
    if (s.size() == 9)
    {
        query.prepare("UPDATE voiture SET matricule =:mat WHERE ROWID=:rowid");
        query.bindValue(":mat", val);
        query.bindValue(":rowid", "1");

            msgBox.setText(QString::number(row));

        return query.exec();
    }
    else if (s == "ID")
    {
        query.prepare("UPDATE voiture SET CIN =:cin ROWID =:rowid");
        query.bindValue(":cin", val);
        query.bindValue(":rowid",QString::number(row));
        return query.exec();
    }
    else if (s == "Marque")
    {
        query.prepare("UPDATE voiture SET marque =:marque ROWID =:rowid");
        query.bindValue(":marque", val);
        query.bindValue(":rowid", QString::number(row));
        return query.exec();
    }
    else if (s == "Modele")
    {
        query.prepare("UPDATE voiture SET modele =:modele ROWID =:rowid");
        query.bindValue(":modele", val);
        query.bindValue(":rowid", QString::number(row));
        return query.exec();
    }
    else if (s == "Couleur")
    {
        query.prepare("UPDATE voiture SET couleur =:couleur ROWID =: rowid");
        query.bindValue(":couleur", val);
        query.bindValue(":rowid", QString::number(row));
        return query.exec();
    }

    return query.exec();
}
