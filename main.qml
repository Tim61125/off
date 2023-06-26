import QtQuick
import QtLocation
import QtPositioning
import QtQuick.Controls
import QtMultimedia 5.15
import QtMultimedia


Rectangle {
    width: Qt.platform.os == "android" ? Screen.width : 1660
    height: Qt.platform.os == "android" ? Screen.height : 800
    visible: true
    /*title: map.center + " zoom " + map.zoomLevel.toFixed(3)
           + " min " + map.minimumZoomLevel   + " max " + map.maximumZoomLevel,"454545444"
                   */
      //title:"NanoSpace"

    Plugin {
        id: mapPlugin
        name: "osm" // "maplibregl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(42.874652, 74.633527)
        zoomLevel: 20
        property geoCoordinate startCentroid

        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            onRotationChanged: (delta) => {
                map.bearing -= delta
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            grabPermissions: PointerHandler.TakeOverForbidden
        }
        WheelHandler {
            id: wheel
            rotationScale: 1/120
            property: "zoomLevel"

        }
        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }
        Shortcut {
            enabled: map.zoomLevel < map.maximumZoomLevel
            sequence: StandardKey.ZoomIn
            onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
        }
        Shortcut {
            enabled: map.zoomLevel > map.minimumZoomLevel
            sequence: StandardKey.ZoomOut
            onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
        }


    }
}
