#ifndef FORMATIONWIDGET_H
#define FORMATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QDate>
#include <QVBoxLayout>
#include <QDebug>
struct FormationData {
    int id;
    QString type;
    QString instructeur;
    QDate dateDebut;
    QDate dateFin;
    QString description;
    int nbParticipants;
};
class FormationWidget : public QWidget {
    Q_OBJECT

public:
    explicit FormationWidget(QWidget *parent = nullptr);

    void setFormationData(const FormationData &data);
    FormationData getFormationData() const;
    int getID() const { return m_id; }
    QString getType() const { return m_type; }
    QString getInstructeur() const { return m_instructeur; }
    QDate getDateDebut() const { return m_dateDebut; }
    QDate getDateFin() const { return m_dateFin; }
    QString getDescription() const { return m_description; }
    int getNbParticipants() const { return m_nbParticipants; }

signals:
    void mousePressed();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *typeLabel;
    QLabel *instructeurLabel;
    QLabel *dateDebutLabel;
    QLabel *dateFinLabel;
    QLabel *descriptionLabel;
    QLabel *nbParticipantsLabel;
    QVBoxLayout *layout;

    // Member variables to store formation data
    int m_id;
    QString m_type;
    QString m_instructeur;
    QDate m_dateDebut;
    QDate m_dateFin;
    QString m_description;
    int m_nbParticipants;
};

#endif // FORMATIONWIDGET_H
