qt_add_library(HalperUiContent STATIC)
qt_add_qml_module(HalperUiContent
    URI "content"
    VERSION 1.0
    QML_FILES
        App.qml
    RESOURCES
)
