#include "formationwidget.h"
#include <QMouseEvent>

FormationWidget::FormationWidget(QWidget *parent) : QWidget(parent) {
    m_id = 0;
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
    imageLabel = new QLabel(this);

    QString labelStyleSheet = "QLabel { border: none; }";
    typeLabel->setStyleSheet(labelStyleSheet);
    instructeurLabel->setStyleSheet(labelStyleSheet);
    dateDebutLabel->setStyleSheet(labelStyleSheet);
    dateFinLabel->setStyleSheet(labelStyleSheet);
    descriptionLabel->setStyleSheet(labelStyleSheet);
    nbParticipantsLabel->setStyleSheet(labelStyleSheet);

    layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(typeLabel);
    layout->addWidget(instructeurLabel);
    layout->addWidget(dateDebutLabel);
    layout->addWidget(dateFinLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(nbParticipantsLabel);
     // Add imageLabel to layout

    setStyleSheet("FormationWidget { background-color: white; }");
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

    typeLabel->setText("Type: " + m_type);
    instructeurLabel->setText("Instructeur: " + m_instructeur);
    dateDebutLabel->setText("Date Début: " + m_dateDebut.toString(Qt::ISODate));
    dateFinLabel->setText("Date Fin: " + m_dateFin.toString(Qt::ISODate));
    descriptionLabel->setText("Description: " + m_description);
    nbParticipantsLabel->setText("Nombre de Participants: " + QString::number(m_nbParticipants));

    if (!data.imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(data.imageData);
            QSize imageSize = pixmap.size();

            QSize maxImageSize(100, 100);
            if (imageSize.width() > maxImageSize.width() || imageSize.height() > maxImageSize.height()) {
                pixmap = pixmap.scaled(maxImageSize, Qt::KeepAspectRatio);
            }

            imageLabel->setPixmap(pixmap);
        } else {
        QPixmap defaultPixmap(":/icons/tsawer/x-circle.svg");
                imageLabel->setPixmap(defaultPixmap);
                imageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        }
}

void FormationWidget::mousePressEvent(QMouseEvent *event) {
    emit mousePressed();
    QWidget::mousePressEvent(event);
}

FormationData FormationWidget::getFormationData() const {
    // Return FormationData object with member variables
    FormationData data;
    data.id = m_id;
    data.type = m_type;
    data.instructeur = m_instructeur;
    data.dateDebut = m_dateDebut;
    data.dateFin = m_dateFin;
    data.description = m_description;
    data.nbParticipants = m_nbParticipants;
    // No need to return image data here
    return data;
}
