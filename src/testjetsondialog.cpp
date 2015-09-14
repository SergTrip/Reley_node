#include "testjetsondialog.h"
#include "ui_testjetsondialog.h"

TestJetsonDialog::TestJetsonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestJetsonDialog)
{
    ui->setupUi(this);

    cout << "Testing the GPIO Pins" << endl;

    // The LED
    gpio_export  ( LEDGPIO              );
    // The LED is an output
    gpio_set_dir ( LEDGPIO, OUTPUT_PIN  );
}

TestJetsonDialog::~TestJetsonDialog()
{
    // unexport the LED
    gpio_unexport( LEDGPIO );

    delete ui;
}

void TestJetsonDialog::on_pushButton_Test_pressed()
{
    cout << "Setting the LED on" << endl;
    gpio_set_value( LEDGPIO, HIGH );
}

void TestJetsonDialog::on_pushButton_Test_released()
{

    cout << "Setting the LED off" << endl;
    gpio_set_value( LEDGPIO, LOW );
}

int TestJetsonDialog::gpio_export( unsigned int gpio )
{
    QString filePath(SYSFS_GPIO_DIR);
    filePath += "/export";

    QFile file( filePath );

    qDebug() << file.fileName() << " " << file.exists();

    if ( !file.open(QIODevice::ReadWrite) )
    {
        qDebug() << "Problems..";
        qDebug() << file.errorString();
        return 1;
    }

    QTextStream fileStream(&file);
    fileStream << LEDGPIO;

    file.close();

    return 0;
}

int TestJetsonDialog::gpio_unexport(unsigned int gpio)
{
    QString filePath(SYSFS_GPIO_DIR);
    filePath += "/unexport";

    qDebug() << filePath;

    QFile file( filePath );
    if ( !file.open(QIODevice::ReadWrite) )
    {
        qDebug() <<"Problems..";
        return 1;
    }

    QTextStream fileStream(&file);

    fileStream << LEDGPIO;

    file.close();

    return 0;
}

int TestJetsonDialog::gpio_set_dir(unsigned int gpio, TestJetsonDialog::PIN_DIRECTION out_flag)
{
    QString filePath(SYSFS_GPIO_DIR);
    filePath += "/gpio";
    filePath += QString::number(gpio) += "/direction";

    qDebug() << filePath;

    QFile file( filePath );
    if ( !file.open(QIODevice::WriteOnly) )
    {
        qDebug() <<"Problems..";
        return 1;
    }

    QTextStream fileStream(&file);

    if ( out_flag == OUTPUT_PIN )
        fileStream << "out";
    else
        fileStream << "in";

    file.close();

    return 0;
}

int TestJetsonDialog::gpio_set_value(unsigned int gpio, TestJetsonDialog::PIN_VALUE value)
{
    QString filePath(SYSFS_GPIO_DIR);
    filePath += "/gpio";
    filePath += QString::number(gpio) += "/value";

    qDebug() << filePath;

    QFile file( filePath );

    if ( !file.open(QIODevice::ReadWrite) )
    {
        qDebug() <<"Problems..";
        return 1;
    }


    QTextStream fileStream(&file);

    if (value==LOW)
        fileStream << QString::number(0);
    else
        fileStream << QString::number(1);

    file.close();
    return 0;
}

int TestJetsonDialog::gpio_get_value(unsigned int gpio, unsigned int *value)
{

}

int TestJetsonDialog::gpio_set_edge(unsigned int gpio, char *edge)
{

}

int TestJetsonDialog::gpio_fd_open(unsigned int gpio)
{
//    int     fd;
//    char    buf[MAX_BUF];

//    snprintf( buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio );

//    fd = open(buf, O_RDONLY | O_NONBLOCK );

//    if (fd < 0)
//    {
//        perror("gpio/fd_open");
//    }

//    return fd;
}

int TestJetsonDialog::gpio_fd_close(int fd)
{
//    return close(fd);
}
