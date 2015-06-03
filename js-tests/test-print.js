
var config = {'folder': '/tmp/pg'};
var p = new PerfGear(config);
print('PerfGear.start = ' + p.start());


var m = new Measurement('test/api/constructor');
print('Measurement.publish = ' + m.publish);
print('m.name = ' + m.name);
print('m.type = ' + m.type);
m.hit();
print('m.hitValue = ' + m.hitValue);
print('m.publish() = ' + m.publish());

p.stop();
