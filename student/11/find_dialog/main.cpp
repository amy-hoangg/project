#include "mainwindow.hh"
//This line includes the header file mainwindow.hh,
//which likely contains the declaration of
//the MainWindow class. This allows the MainWindow
//class to be used in this file.

#include <QApplication>
/*
 *This line includes the header file for the
 *QApplication class, which is the entry point
 *for any Qt-based application. It provides
 *functionality for handling events and
 *managing the application's event loop.
 *
 *int argc is the number of command line arguments
 *passed to the program, including the name of the program
 *itself.
 *
 *char *argv[] is an array of character pointers
 *that represent the command line arguments passed to the program.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QApplication a(argc, argv);:
     * This line creates a QApplication
     * object named a, which is responsible
     * for managing the application's event loop
     * and processing user events.
     *
     * MainWindow w;: This line creates an
     * instance of the MainWindow class named w.
     * This likely creates a window or other graphical
     * user interface element that will be displayed to the user.
     */
    MainWindow w;
    w.show();
    // This line displays the MainWindow object w on the screen.
    return a.exec();
    //This line starts the event loop
    //for the application by calling the exec()
    //function of the QApplication object a.
    //This function waits for events to occur and
    //dispatches them to the appropriate event handlers.
    //The return statement ensures that the program exits
    //cleanly when the event loop is terminated.
}

/*
 * In Qt and many other GUI frameworks,
 * an event loop is a central part of the
 * application architecture.
 * The event loop is responsible for
 * processing user input, updating the
 * graphical user interface, and handling
 * system events such as timer events,
 * network events, and other asynchronous events.
 *
 * The event loop is essentially an infinite
 * loop that waits for events to occur
 * and dispatches them to the appropriate
 * event handlers. When an event occurs,
 * such as a mouse click or a timer expiration,
 * the event is added to a queue.
 * The event loop then retrieves the next event
 * from the queue and dispatches it to the
 * appropriate event handler. Once the event
 * handler has finished processing the event,
 * control is returned to the event loop,
 * which then waits for the next event to occur.
 *
 * The event loop is called a "loop" because
 * it is a continuous process that runs
 * indefinitely until the application is closed or
 * terminated. It constantly checks for events
 * and handles them as they occur, giving the user
 * the impression that the application is responsive
 * and reactive to their actions.


 */
