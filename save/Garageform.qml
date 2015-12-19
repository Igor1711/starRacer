import QtQuick 2.3
import Qt3D 2.0
import Qt3D.Shapes 2.0



Rectangle
{

    id: garagearea

    color: "#00000F"
    focus: true
    width: 1366
    height: 768
    Viewport
    {
        id: allview

          navigation: false
          focus: true
          width: parent.width; height: parent.height
          Mesh { id: garage; source: "/home/igor/qt-projects/Space-Racers/models/gameworld/garage.3ds" }
          Mesh { id: spaceship; source: "/home/igor/qt-projects/Space-Racers/models/spaceships/pacer.3ds" }
          Mesh { id: canon; source: "/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"}
          Mesh { id: door1; source: "/home/igor/qt-projects/Space-Racers/models/gameworld/door1.3ds"}
          Mesh { id: door2; source: "/home/igor/qt-projects/Space-Racers/models/gameworld/door2.3ds"}
          Mesh { id: hiper; source: "/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"}
          Item3D {
              mesh:spaceship
              id: spaceship1
              x:-10
              y:1
              z:1.5
              transform:[land]
          Item3D { mesh: canon
              id:gun
              x: 0
              y: 0.2
              z: 0//window.ret()        // levelOfDetail: 10
              transform: Scale3D {scale: 0.2}
          }
          Item3D {mesh: hiper; id: hiperengine; x:0; y:0; z:0}

          }
          Item3D { mesh: garage
              x: 3
              y: 0
              z: 0
              transform: Scale3D  { scale: Qt.vector3d(1, 1.1, 1)}
              Item3D
              {
                  mesh: door1
                  id: door_garage
                  x:-4.75
                  y:0
                  z:0.8
                  transform: [doorscale1]
              }
              Item3D
              {
                  mesh: door2
                  id: door_shluse
                  x:3.0
                  y:0
                  z:-3.85
                  transform: [doorscale]
                  effect: Effect
                  {
                      id: ef1
                      blending: true
                      color: "#00FFFF"
                      material: glass

                  }

              }

        }



          camera: Camera {
              id: viewCamera
              eye: Qt.vector3d(-0.1,2,-4.5)
              center: Qt.vector3d(1.4,1.9,-9)
              nearPlane: 0.9
              //projectionType: Orthographic


          }
          MouseArea
          {
              id: to_home
              width: parent.width/10
              height: parent.height
              x:0
               onClicked: {
              viewCamera.eye=Qt.vector3d(-0.1, 2, -4.5)
              viewCamera.center=Qt.vector3d(1.4, 1.9, -9)
                   comp.enabled=true
                   ship.enabled=false
                   properties.text=""
              }
          }
          MouseArea
          {
              id: to_garage
              width: parent.width/10
              height: parent.height
              anchors.right: parent.right
              onClicked: {
                  viewCamera.eye=Qt.vector3d(-0.1, 2, -5.5)
                  viewCamera.center=Qt.vector3d(2, 1.8, 2)
                  viewCamera.nearPlane=0.9
                  comp.enabled=false
                  ship.enabled=true
                  //properties.text="123"+"\n"+"456"+"\n"+"678"
                  properties.text=window.give_info(0)+"\n"+window.give_info(1)+"\n"+window.give_info(2)
                  if (window.give_type()===1)
                  {
                      spaceship1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/pacer.3ds"
                      gun.y=0.2
                      gun.x=0
                      hiperengine.x=0.5
                  }
                  if (window.give_type()===2)
                  {
                      spaceship1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/gazlock.3ds"
                      gun.y=0
                      gun.x=1.5
                      hiperengine.x=0.5
                  }
                  if (window.give_type()===3)
                  {
                      spaceship1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/cutter.3ds"
                      gun.y=0
                      gun.x=1.5
                      hiperengine.x=0.75
                  }
                  if (window.give_type()===4)
                  {
                      spaceship1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/shark.3ds"
                      gun.y=0.15
                      gun.x=0
                      hiperengine.x=0.75
                  }
                  if (window.give_type()===5)
                  {
                      spaceship1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/spider.3ds"
                      gun.y=0.05
                      gun.x=1.2
                      hiperengine.x=0.3
                  }
                  if (window.get_gun_info()===1) gun.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds"
                  if (window.get_gun_info()===2) gun.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds"
                  if (window.get_eng(1)===1) hiper.source="/home/igor/qt-projects/Space-Racers/models/spaceships/hiperengine.3ds"
                  if (window.deliver_ship())
                  {
                      ship_delivery.loops=1;
                      ship_delivery.start();

                  }
                  else spaceship1.x=window.ret()


              }
          }
          MouseArea
          {

              width: parent.width/5
              height: parent.height
              anchors.right: to_garage.left
              id: comp
              onClicked:{
                  window.switchcomp_on()
              }
          }
          MouseArea
          {

              width: parent.width/3
              height: parent.height
              anchors.right: comp.left
              id: ship
              onClicked:{
                 window.fly_out()
              }
              enabled:false
          }
          Text
          {
              id: properties
              text: ""
              anchors.left: to_home.right
              width:parent.width/2
              height: parent.height/2
              color: "#FF0000"
              font.pointSize: 20
              font.bold: true

         }
         Rotation3D
         {
              id: land
              angle: 0
              axis: Qt.vector3d(0,1,0)
         }
         Rotation3D
         {
              id: door
              angle: 90
              axis: Qt.vector3d(0,1,0)
         }
         Scale3D
         {
              id: doorscale
              scale: Qt.vector3d(1.6,1.3,0.3)
         }
         Scale3D
         {
              id: doorscale1
              scale: Qt.vector3d(1,1.3,1.5)
         }
         Material
         {

              id: glass
              diffuseColor:Qt.rgba(0,1,1,0.1)
         }
         SequentialAnimation{
    id: ship_delivery;
    NumberAnimation{target: spaceship1; property: "x"; from: -10; to: -9; duration: 40; easing.type: Easing.Linear
    }
    NumberAnimation{target: door_shluse; property: "x"; from: 3; to: -1.5; duration: 1000; easing.type: Easing.Linear
    }
    NumberAnimation{target: door_garage; property: "z"; from: 0.8; to: -5; duration: 1500; easing.type: Easing.Linear
    }
    NumberAnimation{target: land; property: "angle"; from: 0; to: 180; duration: 800; easing.type: Easing.Linear
    }
    NumberAnimation{target: spaceship1; property: "x"; from: -10; to: 2; duration: 2000; easing.type: Easing.Linear
    }
    NumberAnimation{target: land; property: "angle"; from: 180; to: 360; duration: 2000; easing.type: Easing.Linear
    }
    NumberAnimation{target: door_garage; property: "z"; from: -5; to: 0.8; duration: 1500; easing.type: Easing.Linear
    }
    NumberAnimation{target: door_shluse; property: "x"; from: -1.8; to: 3; duration: 1000; easing.type: Easing.Linear
    }

}
}




}
