#ifndef TESTJETSONDIALOG_H
#define TESTJETSONDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QTextStream>

#include <iostream>
#include <string>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>

using namespace std;

#define SYSFS_GPIO_DIR  "/sys/class/gpio"
#define POLL_TIMEOUT    (3 * 1000)              // 3 seconds
#define MAX_BUF         64


namespace Ui {
class TestJetsonDialog;
}

class TestJetsonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestJetsonDialog(QWidget *parent = 0);
    ~TestJetsonDialog();

private slots:
    void on_pushButton_Test_pressed();

    void on_pushButton_Test_released();

    private:

    enum PIN_DIRECTION
    {
        INPUT_PIN   = 0,
        OUTPUT_PIN  = 1
    };

    enum PIN_VALUE
    {
        LOW     = 0,
        HIGH    = 1
    };

private:
    int gpio_export     ( unsigned int gpio );
    int gpio_unexport   ( unsigned int gpio );

    int gpio_set_dir    ( unsigned int gpio, PIN_DIRECTION out_flag );

    int gpio_set_value  ( unsigned int gpio, PIN_VALUE      value   );
    int gpio_get_value  ( unsigned int gpio, unsigned int   *value  );

    int gpio_set_edge   ( unsigned int gpio, char *edge );

    int gpio_fd_open    ( unsigned int gpio );
    int gpio_fd_close   ( int fd            );

private:
    Ui::TestJetsonDialog *ui;

    unsigned int LEDGPIO    = 57;

};

#endif // TESTJETSONDIALOG_H
