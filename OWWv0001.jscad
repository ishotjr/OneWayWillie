
// OneWayWillie v0.0.1

let h = 2;
let size = 20;

function main () {
    return willie();
}

function willie() {
    
    head = cylinder({r: size, h: h, center: false});
    // 0.95" 96x64 color OLED
    oled = cube({size: [22, 15, h]}).translate([-22/2,-15/2,0]);
    head = difference(head, oled);
    
    
    tummy = cylinder({r: 1.5 * size, h: h, center: false}).translate([0,2*size,0]);
    // GP2Y0A60SZLF IR sensor
    ir = cube({size: [24, 10, h]}).translate([-24/2,2*size-10,0]);
    tummy = difference(tummy, ir);
    
    
    body = union(head, tummy);

    return body;
}
