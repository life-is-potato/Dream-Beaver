#include "formationwidget.h"
#include <QMouseEvent>

FormationWidget::FormationWidget(QWidget *parent) : QWidget(parent) {
    // Initialize member variables
    m_id = 0; // Default value for ID
    m_type = "";
    m_instructeur = "";
    m_dateDebut = QDate();
    m_dateFin = QDate();
    m_description = "";
    m_nbParticipants = 0;

    // Create QLabel objects
    typeLabel = new QLabel(this);
    instructeurLabel = new QLabel(this);
    dateDebutLabel = new QLabel(this);
    dateFinLabel = new QLabel(this);
    descriptionLabel = new QLabel(this);
    nbParticipantsLabel = new QLabel(this);

    // Set style sheet for QLabel objects
    QString labelStyleSheet = "QLabel { border: 2px solid white; }";
    typeLabel->setStyleSheet(labelStyleSheet);
    instructeurLabel->setStyleSheet(labelStyleSheet);
    dateDebutLabel->setStyleSheet(labelStyleSheet);
    dateFinLabel->setStyleSheet(labelStyleSheet);
    descriptionLabel->setStyleSheet(labelStyleSheet);
    nbParticipantsLabel->setStyleSheet(labelStyleSheet);

    // Create QVBoxLayout
    layout = new QVBoxLayout(this);

    // Add QLabel objects to layout
    layout->addWidget(typeLabel);
    layout->addWidget(instructeurLabel);
    layout->addWidget(dateDebutLabel);
    layout->addWidget(dateFinLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(nbParticipantsLabel);
}

void FormationWidget::setFormationData(const FormationData &data) {
    // Set member variables using formation data
    m_id = data.id;
    m_type = data.type;
    m_instructeur = data.instructeur;
    m_dateDebut = data.dateDebut;
    m_dateFin = data.dateFin;
    m_description = data.description;
    m_nbParticipants = data.nbParticipants;

    // Update QLabel text
    typeLabel->setText("Type: " + m_type);
    instructeurLabel->setText("Instructeur: " + m_instructeur);
    dateDebutLabel->setText("Date Début: " + m_dateDebut.toString(Qt::ISODate));
    dateFinLabel->setText("Date Fin: " + m_dateFin.toString(Qt::ISODate));
    descriptionLabel->setText("Description: " + m_description);
    nbParticipantsLabel->setText("Nombre de Participants: " + QString::number(m_nbParticipants));
}

void FormationWidget::mousePressEvent(QMouseEvent *event) {
    // Call base class implementation if needed
    emit mousePressed();
    QWidget::mousePressEvent(event);

    // Emit your own custom signal or perform any action you want on mouse click
}

FormationData FormationWidget::getFormationData() const {
    // Return the formation data stored in member variables
    FormationData data;
    data.id = m_id;
    data.type = m_type;
    data.instructeur = m_instructeur;
    data.dateDebut = m_dateDebut;
    data.dateFin = m_dateFin;
    data.description = m_description;
    data.nbParticipants = m_nbParticipants;
    return data;
}
