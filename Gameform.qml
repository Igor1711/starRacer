import QtQuick 2.3
import Qt3D 2.0
import Qt3D.Shapes 2.0


Rectangle {
    id: form
    color: "#00001F"
    width: 1366
    height: 768
    Timer{id:time; interval: 20; repeat: true; onTriggered: run();}
    Viewport
    {
        id:raceview
        width: parent.width; height: parent.height
        Mesh {id: lasering; source:"./3dmodels/spaceships/shotlas.3ds"}
        Mesh {id: gun; source: "./3dmodels/spaceships/nogun.3ds" }
        Mesh {id: second11; source: "./3dmodels/spaceships/first.3ds" }
        Mesh {id: spaceship; source: "./3dmodels/spaceships/pacer.3ds" }
        Mesh {id: engine; source:"./3dmodels/spaceships/turbine.3ds"}
        Mesh {id: garage; source:"./3dmodels/gameworld/garage.3ds"}
        Mesh {id: door1; source: "./3dmodels/gameworld/door1.3ds"}
        Mesh {id: door2; source: "./3dmodels/gameworld/door2.3ds"}
        Mesh {id: glass1; source: "./3dmodels/gameworld/protection1.3ds"}
        Mesh {id: police; source: "./3dmodels/gameworld/police.3ds"}
        Mesh {id: hiper; source: "./3dmodels/spaceships/nogun.3ds"}
        Mesh {id: pont; source: "./3dmodels/gameworld/pont.3ds"}
        Mesh {id: rocket; source:"./3dmodels/spaceships/rocket.3ds"}
        Mesh {id: oppon; source:"./3dmodels/spaceships/pacer.3ds";}
        Mesh {id: oppon1; source:"./3dmodels/spaceships/gazlock.3ds";}
        Mesh {id: oppon2; source:"./3dmodels/spaceships/cutter.3ds";}
        Mesh {id: oppon3; source:"./3dmodels/spaceships/shark.3ds";}
        Mesh {id: oppon4; source:"./3dmodels/spaceships/spider.3ds";}
        Mesh {id: op1can; source:"./3dmodels/spaceships/nogun.3ds";}
        Mesh {id: markaer; source:"./3dmodels/gameworld/marker.3ds";}
        Mesh {id: tanker; source:"./3dmodels/spaceships/transport2.3ds";}
        Mesh {id: tanker_door; source:"./3dmodels/spaceships/tanker_cover.3ds";}
        Mesh {id: shield; source:"./3dmodels/spaceships/shield.3ds";}
        Mesh {id: gener_ship; source:"./3dmodels/gameworld/generation_ship.3ds";}
        Mesh {id: gener_ring; source:"./3dmodels/gameworld/generation_ship_ring.3ds";}
        Mesh {id: prot; source:"./3dmodels/gameworld/st_protect.3ds";}
        Mesh {id: custom; source:"./3dmodels/gameworld/customs.3ds";}
        Mesh {id: postship; source: "./3dmodels/gameworld/pace2.3ds";}
        Mesh {id:scanner; source:"./3dmodels/gameworld/scanner.3ds";}
        Mesh {id:tubes; source:"./3dmodels/gameworld/terminal_tubes.3ds";}
        Mesh {id:terminal; source:"./3dmodels/gameworld/terminal.3ds";}
        Mesh {id: transport1; source: "./3dmodels/spaceships/transport1.3ds"}
        Mesh {id:rep; source:"./3dmodels/gameworld/repair.3ds";}
        property Item3D track: track
        property int checkload: 0
        Text
        {
            id: text
            width:parent.width/7
            height:parent.height
            anchors.right: raceview.right
            text: " "
            color: "#FF0000"
            font.pointSize: 10
            font.bold: true
        }
        Rotation3D {id:turn; angle:0; axis: Qt.vector3d(0, 1, 0);}
        Rotation3D {id:updown; angle:0; axis:Qt.vector3d(0, 0, 1);}
        Rotation3D {id:rotate; angle:0; axis:Qt.vector3d(1, 0, 0);}
        Rotation3D {id:movetourel; angle:0; axis:Qt.vector3d(0,1,0);}
        Scale3D {id:tourel; scale: 0.2;}
        Scale3D {id: shot1; scale: Qt.vector3d(1, 1, 1);}
        Scale3D {id: shot2; scale: 1;}
        Scale3D {id: doorscale; scale: Qt.vector3d(1.6,1.3,0.3);}
        Scale3D {id: doorscale1; scale: Qt.vector3d(1,1.3,1.5);}
        Scale3D {id: ringsize; scale: 2.5;}
        Rotation3D {id: tanker_d1; angle:0; axis: Qt.vector3d(1,0,0);}
        Rotation3D{id:mark; angle: 0; axis:Qt.vector3d(0,1,0);}

        Item3D
        {
            id: generationship;
            y:500;
            mesh: gener_ship;
            Item3D{id:ring1; mesh:gener_ring; z:0.005; transform: Rotation3D{id:ring11;angle:0; axis: Qt.vector3d(1,0,0);}}
            Item3D{id:ring2; mesh:gener_ring; x: -6.2; y: 0.04; z:-0.005; transform: Rotation3D{id: ring12; angle:0; axis: Qt.vector3d(-1,0,0);}}
            Item3D{mesh:custom}
            Item3D{ mesh: rep;}
            Item3D
            {
                mesh:Mesh{source:"./3dmodels/gameworld/garage1.3ds"}
                x:-2.3
                y:-0.045
                z:0.35
                transform: [Rotation3D{angle:180; axis:Qt.vector3d(0,1,0)},Scale3D{scale:0.0025}]
                Item3D{ mesh: door1; x:-4.75; y:0; z:-5; transform: [doorscale1]}

                Item3D
                {
                    mesh: door2
                    x:-1.5
                    y:0
                    z:-3.85
                    transform: [doorscale]
                    effect: Effect
                    {
                        blending: true
                        color: "#00FFFF"
                        material: Material {diffuseColor:Qt.rgba(0,1,1,0.8);}
                    }                
                }

            }
            Item3D
            {
                mesh:prot
                effect: Effect{id: ef5; blending: true;material: Material {diffuseColor:Qt.rgba(0,1,1,0.2);}}
            }
            Item3D
            {
                id:scan;mesh:scanner;y:0;effect: Effect{id: ef8; color: "#00FF00";blending: true;material: Material {emittedLight:Qt.rgba(0,1,0,0.5);}}
            }

            transform: [Scale3D{scale:500}, Rotation3D{id: n21;angle:90; axis: Qt.vector3d(0,1,0)}]
        }
        Item3D{mesh:postship; x:331; y:479; z:816}
        Item3D{mesh:transport1; x:338; y:485; z:740}
        Item3D{mesh:transport1; x:-250; y:500; z:778; transform: [Scale3D{scale:4}, Rotation3D{id: tr_move; angle:180; axis:Qt.vector3d(0,1,0)}]}


        Item3D {id:policeship; mesh:police; x:-429; y:480; z:289;}
        Item3D {id:policeship1; mesh:police; x:271; y:479; z:845; transform:Rotation3D{id: cop2_move;angle:-45;axis:Qt.vector3d(0,1,0) }}
        Item3D {id:policeship2; mesh:police; x:258; y:479; z:845; transform:Rotation3D{id: cop3_move;angle:-45;axis:Qt.vector3d(0,1,0) } }
        Item3D
        {
           id:tanker1; mesh:tanker; x:-200; y:498; z:10000; transform: [Rotation3D {id: tank_move; angle:45; axis: Qt.vector3d(0,1,0);}, Scale3D{scale: 5}]
           Item3D{id: tanker_d; mesh: tanker_door; transform: tanker_d1}
        }
        Item3D {id:tube; mesh: tubes;x:0; y:500; z:300; transform: Scale3D{scale:5}}
        Item3D {id:terminal1; mesh: terminal;x:0; y:500; z:350; transform: Scale3D{scale:5}}
        Item3D{id:marker1; x:-450;y:500; z:0;effect: Effect{id: glowl;blending: true; material: Material{emittedLight: Qt.rgba(0,1,0,0.1)} } mesh: markaer;
    transform:[mark, ringsize]
}
        Item3D
        {
            id:myship
            property real width1:1.75
            property real rs: 1
            x:-65
            y:30
            z:107
            transform: turn
            Item3D
            {
                id: mycorpus
                mesh:spaceship
                transform: [updown,rotate]
                Item3D {id: hiperengine; mesh: hiper;x:0;y:0;z:0;}

                Item3D {id:rock1; x:1; y:1.2; z:1.75; mesh:rocket; }

            Item3D
            {
                 id: canon
                 mesh:gun
                 x:0
                 y:0.2
                 z:0
                 transform: [tourel, movetourel]
                 Item3D
                 {
                     id: laser
                     mesh: lasering
                     x:0
                     z:0
                     y:3
                     transform: [shot1, shot2]
                     effect: Effect
                     {
                          blending: true
                          material: Material{emittedLight: Qt.rgba(0,1,0,0.1)}
                     }
                     Item3D{id: sec_laser;mesh: lasering; x:0; y:0; z:0; transform: [shot1, shot2]}
                 }
             }
            Item3D {id:shield1; x:0.5; mesh: shield; transform: Scale3D{id: sh1;scale:1} effect:Effect{blending: true;
                color: "#00FF0F"; material: Material {diffuseColor:Qt.rgba(0,1,1,0.3);}}}

             }
        }
        Item3D{id:counter; x:-674; y:483; z:429; mesh:second11; transform: Rotation3D{id: counting; angle:90; axis: Qt.vector3d(0,1,0)}}
        Item3D{id: track; x:0.1;y:0; z:0;}
        Item3D
        {
            id: opponent1; x:0; y:0; z:105; mesh: oppon;
            transform: [Rotation3D {angle:90; axis:Qt.vector3d(0,1,0);},Rotation3D {angle:0; axis:Qt.vector3d(1,0,0)}]
            Item3D{ id: canon1; x:0; y:0.2; z:0; mesh: Mesh{source:"/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"} transform: Scale3D{scale:0.2}}
        }
        Item3D
        {
            id: opponent2; x:16; y:0; z:105; mesh: oppon1;
            transform: [Rotation3D {angle:90; axis:Qt.vector3d(0,1,0);},Rotation3D {angle:0; axis:Qt.vector3d(1,0,0)}]
            Item3D{ id: canon2; x:1.5; y:0; z:0; mesh: Mesh{source:"/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"} transform: Scale3D{scale:0.2}}
        }
        Item3D
        {
            id: opponent3; x:32; y:0; z:105; mesh: oppon2;
            transform: [Rotation3D {angle:90; axis:Qt.vector3d(0,1,0);},Rotation3D {angle:0; axis:Qt.vector3d(1,0,0)}]
            Item3D{ id: canon3; x:1.5; y:0; z:0; mesh: Mesh{source:"/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"} transform: Scale3D{scale:0.2}}
        }
        Item3D
        {
            id: opponent4; x:48; y:0; z:105; mesh: oppon3;
            transform: [Rotation3D {angle:90; axis:Qt.vector3d(0,1,0);},Rotation3D {angle:0; axis:Qt.vector3d(1,0,0)}]
            Item3D{ id: canon4; x:0; y:0.15; z:0; mesh: Mesh{source:"/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"} transform: Scale3D{scale:0.2}}
        }
        Item3D
        {
            id: opponent5; x:64; y:0; z:105; mesh: oppon4;
            transform: [Rotation3D {angle:90; axis:Qt.vector3d(0,1,0);},Rotation3D {angle:0; axis:Qt.vector3d(1,0,0)}]
            Item3D{ id: canon5; x:1.2; y:0.05; z:0; mesh: Mesh{source:"/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"} transform: Scale3D{scale:0.2}}
        }



    camera: Camera
    {
        id:camera
        eye: Qt.vector3d(3020,-800,3700)
        center: Qt.vector3d(-70,30,-100)
        nearPlane: 0.9
        farPlane: 10000
    }
    Canvas{
        id: panel1
        width: parent.width
        height: parent.height
        onPaint: {
        var ctx=panel1.getContext("2d");
        drawpanel(ctx);
        //time.start();

        }
    }
    //Skybox{
    //    source:"/home/igor/qt-projects/Space-Racers/image/sky/south.png";
    //}


MouseArea
{
    anchors.fill: parent
    onClicked: {

        mycorpus.mesh.source=window1.panel_output(2);
        canon.x=window1.get_data(28)/100;
        canon.y=window1.get_data(29)/100;
        rock1.y=window1.get_data(31)/100;
        myship.rs=window1.get_data(30)/100;
        myship.width1=window1.get_data(32)/100;
        rock1.x=myship.rs;
        rock1.z=myship.width1
        hiperengine.x=window1.get_data(33)/100;
        if (window1.get_data(11)===0)
        {
            laser.y=0
            laser.z=0
            sec_laser.z=0;
        }
        if (window1.get_data(11)===1)
        {
            laser.y=3
            laser.z=0
            sec_laser.z=0;
        }
        if (window1.get_data(11)===2)
        {
           laser.y=3
            laser.z=0.25
            sec_laser.z=-0.5;
        }
        canon.mesh.source=window1.panel_output(3);
        if (window1.get_data(19)===1) hiper.source="/home/igor/qt-projects/Space-Racers/models/spaceships/hiperengine.3ds"
        time.start()
        taker_arrive.loops=50;
        tanker_arrive2.loops=50;
        taker_arrive.start();        
        tanker_arrive2.start();
    }
}
    SequentialAnimation
    {
        id:shooting
        NumberAnimation {target: laser; property: "x"; from: 0; to: -10; duration: 100; easing.type: Easing.Linear }
        NumberAnimation {target: laser; property: "x"; from: 0; to: -100; duration: 100; easing.type: Easing.Linear }
    }
    SequentialAnimation
    {
       id:taker_arrive
       NumberAnimation {target: tanker1; property: "z"; from: -10000; to: 450; duration: 25000; easing.type: Easing.OutExpo }
       NumberAnimation {target: tank_move; property: "angle"; from: 45; to: 90; duration: 6000; easing.type: Easing.Linear }
       //NumberAnimation {target: tanker1; property: "x"; from: -200; to: -61; duration: 2000; easing.type: Easing.Linear }
       NumberAnimation {target: scan; property: "y"; from: 0; to: 0.2; duration: 5000; easing.type: Easing.Linear }
       NumberAnimation {target: scan; property: "y"; from: 0.2; to: 0; duration: 5000; easing.type: Easing.Linear }
       NumberAnimation {target: tank_move; property: "angle"; from: 90; to: -15; duration: 8000; easing.type: Easing.Linear }
       NumberAnimation {target: tanker1; property: "x"; from: 477; to: 0; duration: 9000; easing.type: Easing.Linear }
       NumberAnimation {target: tank_move; property: "angle"; from: -15; to: 0; duration: 2000; easing.type: Easing.Linear }
       NumberAnimation{target: tanker_d1; property: "angle"; from: 0; to:-35; duration: 1000;easing.type: Easing.Linear }
       NumberAnimation{target: tube; property: "z"; from: 300; to: 350; duration: 1000;easing.type: Easing.Linear}
       NumberAnimation{target: tube; property: "z"; from: 350; to: 351; duration: 30000;easing.type: Easing.Linear}
       NumberAnimation{target: tube; property: "z"; from: 350; to: 300; duration: 1000;easing.type: Easing.Linear}
       NumberAnimation{target: tanker_d1; property: "angle"; from: -35; to:0; duration: 1000;easing.type: Easing.Linear }
       NumberAnimation{target: tank_move; property: "angle"; from: 0; to:180; duration: 8000;easing.type: Easing.Linear }
       NumberAnimation {target: tanker1; property: "x"; from: 0; to: 477; duration: 9000; easing.type: Easing.Linear }
       NumberAnimation {target: tank_move; property: "angle"; from: 180; to: 225; duration: 5000; easing.type: Easing.Linear }
       NumberAnimation {target: tanker1; property: "z"; from: 483; to: -10000; duration: 25000; easing.type: Easing.InExpo }
       NumberAnimation{target: tanker1; property: "y"; from: 498; to: 500; duration: 65000; easing.type: Easing.Linear }



    }
    SequentialAnimation
    {
       id:tanker_arrive2
       NumberAnimation {target: tanker1; property: "x"; from: 10000; to: 477; duration: 25000; easing.type: Easing.OutExpo }
       NumberAnimation {target: tanker1; property: "z"; from: 450; to: 483; duration: 1000; easing.type: Easing.OutExpo }
       NumberAnimation{target: tanker1; property: "y"; from: 498; to: 500; duration: 23000; easing.type: Easing.Linear }
       NumberAnimation{target: tanker1; property: "z"; from: 483; to: 350; duration: 9000; easing.type: Easing.Linear }
       NumberAnimation{target: tanker1; property: "y"; from: 498; to: 500; duration: 36000; easing.type: Easing.Linear }
       NumberAnimation {target: tanker1; property: "z"; from: 350; to: 483; duration: 8000; easing.type: Easing.Linear }
       NumberAnimation{target: tanker1; property: "y"; from: 498; to: 500; duration: 16000; easing.type: Easing.Linear }

       NumberAnimation {target: tanker1; property: "x"; from: 477; to: 10000; duration: 25000; easing.type: Easing.InExpo }
       NumberAnimation {target: tank_move; property: "angle"; from: 135; to: 45; duration: 65000; easing.type: Easing.Linear }



    }
    SequentialAnimation
    {
        id:counting1
        NumberAnimation{target:counting; property: "angle"; from:180; to: 0; duration:1500; easing.type: Easing.Linear}
        NumberAnimation{target:counting; property: "angle"; from:180; to: 0; duration:1500; easing.type: Easing.Linear}
        NumberAnimation{target:counting; property: "angle"; from:180; to: 90; duration:1000; easing.type: Easing.Linear}

    }
    SequentialAnimation
    {
        id:rocketshot
        NumberAnimation{target:rock1;property: "z"; from: myship.width1; to: (myship.width1+0.2); duration:100; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "x"; from: myship.rs; to: -80; duration:400; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "z"; from: (myship.width1+0.2); to: myship.width1; duration:100; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "x"; from: -80; to: myship.rs; duration:10; easing.type: Easing.Linear}
    }
    SequentialAnimation
    {
        id:rocketshot2
        NumberAnimation{target:rock1;property: "z"; from: -myship.width1; to: -(myship.width1+0.2); duration:100; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "x"; from: myship.rs; to: -80; duration:400; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "z"; from: -(myship.width1+0.2); to: -myship.width1; duration:40; easing.type: Easing.Linear}
        NumberAnimation{target:rock1;property: "x"; from: -80; to: myship.rs; duration:10; easing.type: Easing.Linear}
    }
}
    function run()
    {
        var p1;
        ring11.angle+=0.25;
        ring12.angle+=0.25;
        movetourel.angle=window1.get_data(10);
        turn.angle=window1.get_data(16)//+window1.get_data(4)
        rotate.angle=0.5*window1.get_data(4);
        myship.x=window1.get_data(0)/100;
        myship.z=window1.get_data(1)/100;
        myship.y=window1.get_data(2)/100;
        updown.angle=window1.get_data(20);
        if (window1.get_data(13)===1)
        {
            shot1.scale=Qt.vector3d(100,1,1);
            //shooting.loops=1
            //shooting.start()
            window1.shot1();
        }
        else
        {
            laser.x=0;
            shot1.scale.x=1;
        }
        camera.eye=Qt.vector3d(myship.x+window1.get_data(17)/100,0,myship.z+window1.get_data(18)/100);
        camera.center=Qt.vector3d(myship.x,myship.y,myship.z);
        camera.eye.y=myship.y+window1.get_data(21)/100;
        panel1.requestPaint();
        if (window1.get_data(25)>10 && raceview.checkload<20)
        {
            loadtrack();
        }
        if (window1.start()) text.text="\n \n \n \n \n \n \n\n"+window1.panel_output(1)+'\n'+window1.get_data(34).toString();
        else text.text="";
        if (window1.start()===false && raceview.checkload>10) removetrack();
        opponent1.x=window1.get_op_data(0)/100;
        opponent1.y=window1.get_op_data(1)/100;
        opponent1.z=window1.get_op_data(2)/100;
        opponent1.transform[0].angle=window1.get_op_data(3);
        opponent1.transform[1].angle=window1.get_op_data(4);
        opponent2.x=window1.get_op_data(10)/100;
        opponent2.y=window1.get_op_data(11)/100;
        opponent2.z=window1.get_op_data(12)/100;
        opponent2.transform[0].angle=window1.get_op_data(13);
        opponent2.transform[1].angle=window1.get_op_data(14);
        opponent3.x=window1.get_op_data(20)/100;
        opponent3.y=window1.get_op_data(21)/100;
        opponent3.z=window1.get_op_data(22)/100;
        opponent3.transform[0].angle=window1.get_op_data(23);
        opponent3.transform[1].angle=window1.get_op_data(24);
        opponent4.x=window1.get_op_data(30)/100;
        opponent4.y=window1.get_op_data(31)/100;
        opponent4.z=window1.get_op_data(32)/100;
        opponent4.transform[0].angle=window1.get_op_data(33);
        opponent4.transform[1].angle=window1.get_op_data(34);
        opponent5.x=window1.get_op_data(40)/100;
        opponent5.y=window1.get_op_data(41)/100;
        opponent5.z=window1.get_op_data(42)/100;
        opponent5.transform[0].angle=window1.get_op_data(43);
        opponent5.transform[1].angle=window1.get_op_data(44);
        if (window1.get_data(35) === 1) sh1.scale=20;
        else sh1.scale=1;
        if (window1.get_data(25)===58)
        {
            counting1.loops=1;
            counting1.start();
        }
        if (window1.get_data(25)===0) second11.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds"
        if (window1.get_data(25)>0 && window1.get_data(25)<21) second11.source="/home/igor/qt-projects/Space-Racers/models/spaceships/first.3ds"
        if (window1.get_data(25)>20 && window1.get_data(25)<41) second11.source="/home/igor/qt-projects/Space-Racers/models/spaceships/second.3ds"
        if (window1.get_data(25)>40) second11.source="/home/igor/qt-projects/Space-Racers/models/spaceships/third.3ds"
        if (window1.get_data(26)===12)
        {
            rocketshot.loops=1;
            rocketshot.start();
            window1.rocket();
        }
        if (window1.get_data(26)===11)
        {
            rocketshot2.loops=1;
            rocketshot2.start();
            window1.rocket();
        }
        if (window1.finished()) removetrack();
        if (window1.start())
        {
            p1=window1.get_point(121);
            marker1.x=window1.get_point(p1);
            marker1.y=window1.get_point(p1+60);
            marker1.z=window1.get_point(p1+30);
            mark.angle=window1.get_point(p1+90);            
        }
        else
        {
            marker1.z=-450;
            marker1.y=500;
            marker1.x=0;
        }
    }
    function loadtrack()
    {
       var k=0, x=50,y=100,z=10,a=0,n;
        var pointing
        raceview.track=Qt.createQmlObject('import QtQuick 2.3; import Qt3D 2.0; Item3D {id: track; x:0.1; y:0; z:0; }', raceview, "ring.qml")
        while (k<20)
        {
           n="point"+(k+15).toString()
           x=window1.get_point(k);
           z=window1.get_point(k+30);
           y=window1.get_point(k+60);
           a=window1.get_point(k+90);
           var point15=Qt.createQmlObject('import QtQuick 2.3; import Qt3D 2.0; Item3D {id: '+n+'; mesh: pont; x:'+x.toString()+'; y:'+y.toString()+'; z:'+z.toString()+'; transform:[Scale3D{scale:ringsize.scale}, Rotation3D{angle: '+a.toString()+'; axis:Qt.vector3d(0,1,0)}]}', raceview.track, "ring.qml")
           raceview.checkload++;
           k++;
        }
        ringsize.scale = window1.get_data(34)/10
        mark.axis=Qt.vector3d(0,1,0);
        if (window1.get_op_data(5)===1) canon1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds";
        if (window1.get_op_data(5)===2) canon1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds";
        if (window1.get_op_data(5)===3) canon1.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds";
        if (window1.get_op_data(15)===1) canon2.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds";
        if (window1.get_op_data(15)===2) canon2.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds";
        if (window1.get_op_data(15)===3) canon2.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds";
        if (window1.get_op_data(25)===1) canon3.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds";
        if (window1.get_op_data(25)===2) canon3.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds";
        if (window1.get_op_data(25)===3) canon3.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds";
        if (window1.get_op_data(35)===1) canon4.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds";
        if (window1.get_op_data(35)===2) canon4.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds";
        if (window1.get_op_data(35)===3) canon4.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds";
        if (window1.get_op_data(45)===1) canon5.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/nogun.3ds";
        if (window1.get_op_data(45)===2) canon5.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/lasegun.3ds";
        if (window1.get_op_data(45)===3) canon5.mesh.source="/home/igor/qt-projects/Space-Racers/models/spaceships/doublegun.3ds";
        window1.finishload();
    }
    function removetrack()
    {
        var k=1,x,y,z;
        raceview.track.destroy();
        raceview.checkload=0;
        window1.finish();
    }

    function drawpanel(ctx)
    {
        ctx.lineWidth=4;
        ctx.strokeStyle="rgb(150,200,250)";
        ctx.strokeRect(0,0, panel1.width/4, 100)
        ctx.strokeRect(panel1.width/4, 0, panel1.width/4, 100);
        ctx.strokeRect(panel1.width/2, 0, 200, 100);
        ctx.strokeRect(panel1.width/2+200, 0, panel1.width/2-100, 100);
        ctx.lineWidth=4;
        ctx.strokeStyle="rgb(200,200,200)";
        ctx.moveTo(25,25);
        ctx.lineTo(70,30);
        ctx.stroke();
        ctx.lineWidth=1;
        ctx.strokeStyle="rgb(0,0,200)";
        ctx.moveTo(25,25);
        ctx.lineTo(70,30);
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(40,40);
        ctx.lineTo(47,35);
        ctx.lineTo(67,35);
        ctx.lineTo(72,22);
        ctx.lineTo(92,22);
        ctx.lineTo(102,40);
        ctx.lineTo(40,40);
        ctx.closePath();
        ctx.fillStyle="rgb(200,250,250)";
        ctx.stroke();
        ctx.fill();
        ctx.fillStyle="rgb(0,0,0)";
        ctx.fillRect(120,20,100,20);
        ctx.fillRect(120,70,100,20);
        ctx.fillRect(panel1.width/4+50,25,100,50);
        ctx.fillRect(panel1.width/4+170, 10, 100,20);
        ctx.fillRect(panel1.width/4+170, 40, 100,20);
        ctx.fillRect(panel1.width/4+170, 70, 100,20);
        ctx.fillRect(panel1.width/2+300, 15,100,20);
        ctx.fillRect(raceview.width-150, 15, 100, 20);
        ctx.fillRect(raceview.width-150, 65, 100, 20);

        ctx.font="12pt Arial";
        ctx.fillStyle="rgb(0,200,0)";
        ctx.fillText("Speed", panel1.width/4+55, 43);
        ctx.fillText(window1.get_data(3).toString()+" mph", panel1.width/4+55, 63);
        ctx.fillText(window1.get_data(15).toString(),130,87);
        ctx.fillRect(120,20,window1.get_data(6),20);

        ctx.fillText("x:  "+window1.get_data(0)/100, panel1.width/4+175, 28);
        ctx.fillText("y:  "+window1.get_data(2)/100, panel1.width/4+175, 58);
        ctx.fillText("z:  "+window1.get_data(1)/100, panel1.width/4+175, 88);
        ctx.fillRect(raceview.width-150,15, window1.get_data(5),20);
        ctx.fillRect(panel1.width/2+300, 15,window1.get_data(7),20);
        ctx.fillRect(raceview.width-150,65, window1.get_data(8),20);

        ctx.fillStyle="rgb(255,0,0)"
        ctx.fillRect(raceview.width-190,20,30,10);
        ctx.fillRect(raceview.width-180,10,10,30);
        ctx.fillStyle="rgb(0,100,0)";
        ctx.strokeStyle="rgb(0,100,0)";
        ctx.beginPath();
        ctx.arc(50,70,5,0,2*Math.PI,true);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
        ctx.fillRect(50,65,60,10);
        if (window1.rad()) {drawradar(ctx)};
        ctx.fillStyle="rgb(0,250,250)";
        ctx.strokeStyle="rgb(0,250,250)";

        ctx.beginPath();
        ctx.moveTo(panel1.width-185,60);
        ctx.lineTo(panel1.width-170,60);
        ctx.lineTo(panel1.width-180,70);
        ctx.lineTo(panel1.width-165,70);
        ctx.lineTo(panel1.width-190,90);
        ctx.lineTo(panel1.width-180,75);
        ctx.lineTo(panel1.width-191,75);
        ctx.lineTo(panel1.width-185,60);
        ctx.closePath();
        ctx.stroke();
        ctx.fill();

        ctx.beginPath();
        ctx.moveTo(panel1.width/2+250,10);
        ctx.lineTo(panel1.width/2+280,10);
        ctx.lineTo(panel1.width/2+280,25);
        ctx.lineTo(panel1.width/2+265,40);
        ctx.lineTo(panel1.width/2+250,25);
        ctx.lineTo(panel1.width/2+250,10);
        ctx.stroke();
        ctx.fill();
    }
    function drawradar(ctx)
    {
        ctx.fillStyle="rgb(0,100,0)";
        ctx.fillRect(raceview.width/2, 0, 200, 100);
        ctx.fillStyle="rgb(0,150,0)";
        ctx.beginPath();
        ctx.arc(raceview.width/2+50,50,50,0,2*Math.PI,true);
        ctx.closePath();
        ctx.fill();
        ctx.beginPath();
        ctx.arc(raceview.width/2+150,50,50,0,2*Math.PI,true);
        ctx.closePath();
        ctx.fill();
        ctx.strokeStyle="rgb(0,200,0)";
        ctx.beginPath();
        ctx.arc(raceview.width/2+150,50,40,0,2*Math.PI,true);
        ctx.arc(raceview.width/2+150,50,20,0,2*Math.PI,true);
        ctx.arc(raceview.width/2+50,50,40,0,2*Math.PI,true);
        ctx.arc(raceview.width/2+50,50,20,0,2*Math.PI,true);
        ctx.closePath();
        ctx.stroke();
        ctx.moveTo(panel1.width/2,50);
        ctx.lineTo(panel1.width/2+200,50);
        ctx.moveTo(panel1.width/2+50,0);
        ctx.lineTo(panel1.width/2+50,100);
        ctx.moveTo(panel1.width/2+150,0);
        ctx.lineTo(panel1.width/2+150,100);
        ctx.stroke();
        var i=1;
        window1.radaring();
        ctx.fillStyle="rgb(0,255,255)";
        ctx.fillRect(raceview.width/2+50-window1.get_radar(0,1), 50-window1.get_radar(0,2),2,2);
        ctx.fillRect(raceview.width/2+150-window1.get_radar(0,1), 50-window1.get_radar(0,0),2,2);
        ctx.fillStyle="rgb(255,0,0)";
        while (i<25)
        {
            ctx.fillRect(raceview.width/2+50-window1.get_radar(i,1), 50-window1.get_radar(i,2),2,2);
            ctx.fillRect(raceview.width/2+150-window1.get_radar(i,1), 50-window1.get_radar(i,0),2,2);
            i++;
        }
    }
}

