#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include "NodeEditorWidget.h"
#include "NodeEditorScene.h"
#include "LibFilter.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // Menu-File
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    // Menu-Edit
    void addItem();
    void deleteItem();
    // Menu-View
    void scaleCahnged();
    // Menu-Debug
    void debugDrawCahnged(bool checked);
    // Menu-Help
    void help();
    void docs();
    void about();

//    void backgroundButtonGroupClicked(QAbstractButton *button);
//    void buttonGroupClicked(int id);
//    void pointerGroupClicked(int id);
//    void sceneScaleChanged(const QString &scale);
//    void lineColorChanged();
//    void lineButtonTriggered();
//    //void itemSelected(QGraphicsItem *item);
//    void itemInserted(NodeItem* item);


private:
    // Menus/ToolBars/ToolBoxes
    void createMenus();
    void createActions();
    void createToolbars();
    //void createToolBox();


    // MainMenu
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *addItemSubmenu;
    QMenu *debugMenu;
    QMenu *helpMenu;

    // ToolBars
    QToolBar *fileToolbar;
    QToolBar *debugToolbar;

    // ToolBox
    QToolBox * toolBox;
    QButtonGroup *addButtonGroup;

    // Menu-File Actions
    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *exitAction;
    // Menu-Edit Actions
    QVector<QAction*> addItemActionVector;
    QAction *deleteItemAction;
    // Menu-Debug Actions
    QAction *debugDrawAction;
    // Menu-Help Actions
    QAction *helpAction;
    QAction *docsAction;
    QAction *aboutAction;

    // Node Editor
    NodeEditorWidget * nodeEditorWidget;
    NodeEditorScene * nodeEditorScene;

    // Filters
    LibFilter libFilter;

};

