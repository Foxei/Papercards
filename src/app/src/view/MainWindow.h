/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file MainWindow.h
 */
#ifndef PAPERCARDS_MAIN_WINDOW_H
#define PAPERCARDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QFrame>

#include "card/CardEditor.h"
#include "src/view/card/CardEditorToolBar.h"
#include "base/StatusBar.h"

#include "model/Model.h"

/**
 * @brief The main window for the papercards application
 * @details The main window will have a edit/view area in the center of the
 * window, a toolbar to edit the text on the top and a statusbar at the bottom.
 */
class MainWindow : public QMainWindow {
 Q_OBJECT
 private:
  /**
   * @brief Card editor in the center of the window
   */
  CardEditor *card_editor = Q_NULLPTR;
  /**
   * @brief ToolBar at the top to edit the text font, types and sizes in the
   * editor
   */
  CardEditorToolBar *card_editor_toolbar = Q_NULLPTR;
  /**
   * @brief StatusBar at the bottom to show messages and zoom without a scroll
   * wheel.
   */
  StatusBar *status_bar = Q_NULLPTR;

  QApplication *application_ = Q_NULLPTR;

  /**
   * @brief Setup all window elements and there behavior that don't include
   * interaction with other widgets.
   */
  void setupGui();
  /**
   * @brief Setup all connections for the interactions between elements.
   */
  void setupConnections();

  /**
   * @brief Will restore the window state from the last season.
   */
  void restoreWindowStates();

  /**
   * @brief Will store the window state from the current season.
   */
  void storeWindowState();

 private slots:

  void handleFocusChanged(QWidget *old_widget, QWidget *new_widget);

 protected:

  /**
   * @brief Will store the current window state to a file so it can be loaded
   * at the next start.
   * @param event Event with details about the circumstances of the close.
   */
  void closeEvent(QCloseEvent *event) override;

 public:

  /**
   * @brief Will setup the main window and then will restore all settings from
   * the last season.
   * @param parent Parent of this window.
   * @param flags Flags for this window.
   */
  explicit MainWindow(QApplication *application, QWidget *parent = Q_NULLPTR,
                      Qt::WindowFlags flags = Qt::WindowFlags());

  signals:

  void showCardInEditor(Card* card);

};

#endif //PAPERCARDS_MAIN_WINDOW_H
