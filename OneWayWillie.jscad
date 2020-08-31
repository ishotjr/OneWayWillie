
// OneWayWillie v0.0.3

let h = 2;
let walls = 21 * h;
let size = 20;

function main () {
    return willie();
}

function willie() {
    
    head = cylinder({r: size, h: walls, center: false});
    brain = cylinder({r: size - h, h: walls - h, center: false}).translate([0,0,h]);
    // 0.95" 96x64 color OLED
    oled = cube({size: [22, 15, walls]}).translate([-22/2,-15/2,0]);
    pins = cube({size: [22, 5, walls]}).translate([-22/2,-15/2-5,h/2]);
    head = difference(head, brain, oled, pins);
    
    
    tummy = cylinder({r: 1.5 * size, h: walls, center: false}).translate([0,2*size,0]);
    stomach = cylinder({r: 1.5 * size - h, h: walls - h, center: false}).translate([0,2*size,h]);
    // GP2Y0A60SZLF IR sensor
    ir = cube({size: [24, 10, walls]}).translate([-24/2,2*size-10-10,0]);
    piezo = cylinder({r: 22.5/2, h: walls, center: false}).translate([0,2.5*size,0]);
    tummy = difference(tummy, stomach, ir, piezo);
    
    stand = cube({size: [24, 2*h, walls]}).translate([-24/2,3.5*size-2*h,0]);
    body = union(head, tummy, stand);
    
    // pcb diff'd with body union and +2 pcb height to delete intersection
    pcb = cube({size: [28, 31+2, walls]}).translate([-28/2,-15/2-5,h]);
    usb = cube({size: [10, 2*h, walls/2]}).translate([-10/2,3.5*size-2*h,walls/2]);
    body = difference(body,pcb, usb);

    return body;
}
