#include "barcodeprinter.h"


BarcodePrinter::BarcodePrinter(QObject *parent) :
    QObject(parent),
    printerConfigured(FALSE)
{

}

QStringList BarcodePrinter::getAvailablePrinters()
{
    QStringList availablePrinters;

    QPrinterInfo pInfo;
    foreach (QPrinterInfo info, pInfo.availablePrinters()) {
        availablePrinters << info.printerName();
    }

    return availablePrinters;
}

bool BarcodePrinter::configurePrinter(QString printerName)
{
    bool printerAvailable = getAvailablePrinters().contains(printerName);
    if(printerAvailable)
    {
        mPrinter.setPrinterName(printerName);
        configurePage();

        qDebug() << "Printer initialized. State:" << mPrinter.printerState();
    }
    else
    {
        mPrinter.setOutputFileName("barcode.pdf");
        mPrinter.setOutputFormat(QPrinter::PdfFormat);
        configurePage();

        qDebug() << "Printer initialized to generate pdf";
    }

    printerConfigured = TRUE;

    return printerAvailable;

}



void BarcodePrinter::printBarcode(QString barcodeText)
{
    if(!printerConfigured)
    {
       QMessageBox::critical(nullptr,"winek","winek") ;
    }
    else {

    int imageWidth = 400; // l width mtee l image
    int imageHeight = 200;// l height mtee l image
    QImage image(imageWidth, imageHeight, QImage::Format_ARGB32);

    image.fill(Qt::white); //7ot bg bitha ll image

    QPainter painter(&image);

    int barcodeWidth = 400; // l width mtee l barcode
    int barcodeHeight = 100; // l hieght mtee l barcode
    int barcodeX = (imageWidth - barcodeWidth) / 2;
    int barcodeY = (imageHeight - barcodeHeight) / 2;
    QRect barcodeRect(barcodeX, barcodeY, barcodeWidth, barcodeHeight);


    int textY = barcodeY + barcodeHeight + 10;
    QRect barcodeTextRect(0, textY, imageWidth, 20);

    QFont barcodefont = QFont("Code 128", 30, QFont::Normal);
    barcodefont.setLetterSpacing(QFont::AbsoluteSpacing, 0.0);
    painter.setFont(barcodefont);

    QString arr = encodeBarcode(barcodeText);
    painter.drawText(barcodeRect, Qt::AlignCenter, arr);

    QFont textFont("PT Sans", 10);
    painter.setFont(textFont);
    painter.drawText(barcodeTextRect, Qt::AlignCenter, barcodeText);

    painter.end();

        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        QSqlQuery q;
        q.prepare("UPDATE EQUIPEMENTS SET BARCODE = :bc WHERE ID = :id ");

        q.bindValue(":bc",byteArray);
        q.bindValue(":id",barcodeText);

        if (!q.exec()) {
            qDebug() << "Error inserting image into database:" << q.lastError().text();
        } else {
            qDebug() << "Image saved successfully!";
        }
    }
}




void BarcodePrinter::configurePage()
{
    //
    mPrinter.setColorMode(QPrinter::GrayScale);
    mPrinter.setPageSizeMM(QSizeF(80,40));
    mPrinter.setPaperSize(QSizeF(80,40), QPrinter::Millimeter);
    mPrinter.setResolution(203);
    mPrinter.setPageMargins(0,0,0,0, QPrinter::Millimeter);
    mPrinter.setOrientation(QPrinter::Portrait);
}

QString BarcodePrinter::encodeBarcode(QString code)
{
    QString encoded;

    encoded.prepend(QChar(codeToChar(CODE128_B_START)));
    encoded.append(code);
    encoded.append(QChar(calculateCheckCharacter(code)));
    encoded.append(QChar(codeToChar(CODE128_STOP)));

    return encoded;
}

int BarcodePrinter::calculateCheckCharacter(QString code)
{
    QByteArray encapBarcode(code.toUtf8());
    long long sum = CODE128_B_START;
    int weight = 1;

    foreach(char ch, encapBarcode) {
        int code_char = charToCode((int)ch); //Calculate character code
        sum += code_char*weight; //add weighted code to sum
        weight++; //increment weight
    }

    int remain = sum%103; //The check character is the modulo 103 of the sum

    //Calculate the font integer from the code integer
    if(remain >= 95)
        remain += 105;
    else
        remain += 32;

    return remain;
}

int BarcodePrinter::codeToChar(int code)
{
    return code + 105;
}

int BarcodePrinter::charToCode(int ch)
{
    return ch - 32;
}
