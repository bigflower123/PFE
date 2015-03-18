#include "tools.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>

Tools::Tools()
{

}

Tools::~Tools()
{

}

/**
 * @brief Tools::debugMessage
 * @param message
 */
void Tools::debugMessage(QString message){
    qDebug("%s", message.toStdString().c_str());
}

/**
 * @brief Tools::debugMessage
 * @param message
 * @param value
 */
void Tools::debugMessage(QString message, bool value){
    qDebug("%s : %s", message.toStdString().c_str(),value ? "true" : "false");
}

/**
 * @brief Tools::debugMessage
 * @param message
 * @param value
 */
void Tools::debugMessage(QString message, int value){
    qDebug("%s : %d", message.toStdString().c_str(),value);
}

/**
 * @brief Tools::debugMessage
 * @param message
 * @param value
 */
void Tools::debugMessage(QString message, QString value){
    qDebug("%s : %s", message.toStdString().c_str(),value.toStdString().c_str());
}

/**
 * @brief Tools::debugMessage
 * @param message
 * @param value
 */
void Tools::debugMessage(QString message, double value){
    qDebug("%s : %f", message.toStdString().c_str(),value);
}

/**
 * @brief Tools::customMessageHandler
 * @param type
 * @param context
 * @param msg
 */
void Tools::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   Q_UNUSED(context);

   QString dt = QDateTime::currentDateTime().toString("hh:mm:ss");
   QString txt = QString("[%1] ").arg(dt);

   switch (type)
   {
      case QtDebugMsg:
         txt += QString("{Debug} \t\t %1").arg(msg);
         break;
      case QtWarningMsg:
         txt += QString("{Warning} \t %1").arg(msg);
         break;
      case QtCriticalMsg:
         txt += QString("{Critical} \t %1").arg(msg);
         break;
      case QtFatalMsg:
         txt += QString("{Fatal} \t\t %1").arg(msg);
         abort();
         break;
   }

   dt = QDateTime::currentDateTime().toString("dd_MM_yyyy");

   //configuration du nom du fichier de log (LogFile_[dateCourante].log)
   QString filenameToCreate = "LogFile_" + dt + ".log";
   QFile outFile(filenameToCreate);

   //ouverture du fichier, soit en Mode Ecriture seule, soit en mode Ajout
   outFile.open(QIODevice::WriteOnly | QIODevice::Append);

   //Ecriture dans fichier de log
   QTextStream textStream(&outFile);
   textStream << txt << endl;

   //Ecriture console
   std::cout << txt.toStdString() << std::endl;

}

/**
 * @brief Tools::cvMatToQPixmap
 * @param inMat
 * @return
 */
QPixmap Tools::cvMatToQPixmap( const cv::Mat &inMat )
   {
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
   }

/**
 * @brief Tools::cvMatToQImage
 * @param inMat
 * @return
 */
QImage Tools::cvMatToQImage( const cv::Mat &inMat ){
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
            break;
      }

      return QImage();
   }

