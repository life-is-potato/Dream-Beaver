#ifndef FORMATIONS_H
#define FORMATIONS_H

#include <QString>
#include <QDate>
#include <QStandardItemModel>
#include "databaseconnection.h"

class Formations
{
private:
    int id;
    QString type;
    QString instructeur;
    QDate dateDebut;
    QDate dateFin;
    QString description;
    int nbParticipants;

public:
    // Constructor
    Formations();

    // Getters
    int get_id() const { return id; }
    QString get_type() const { return type; }
    QString get_instructeur() const { return instructeur; }
    QDate get_dateDebut() const { return dateDebut; }
    QDate get_dateFin() const { return dateFin; }
    QString get_description() const { return description; } // Getter pour la description
    int get_nbParticipants() const { return nbParticipants; }

    // Setters
    void set_id(int x) { id = x; }
    void set_type(const QString &str) { type = str; }
    void set_instructeur(const QString &instr) { instructeur = instr; }
    void set_dateDebut(const QDate &date) { dateDebut = date; }
    void set_dateFin(const QDate &date) { dateFin = date; }
    void set_description(const QString &desc) { description = desc; } // Setter pour la description
    void set_nbParticipants(int nb) { nbParticipants = nb; }

    // Functions
    QStandardItemModel *afficher();
    QStandardItemModel *search_element(const QString &str);
    bool Add_element(int id, QString type, QString instructeur, QDate dateDebut, QDate dateFin, QString description, int nbParticipants,const QByteArray &imageData);
    bool Modify_element(int id, QString type, QString instructeur, QDate dateDebut, QDate dateFin, QString description, int nbParticipants,const QByteArray &imageData);
    bool Delete_element(int x);
        QStandardItemModel *tri_by_type();
};

#endif // FORMATIONS_H
