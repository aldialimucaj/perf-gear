print('hello from dukbridge')

print('PerfGear = ' + PerfGear);
var p = new PerfGear();
print('PerfGear.startPerfGear = ' + p.startPerfGear);

print('Measurement = ' + Measurement);

var m = new Measurement('test/api/constructor');
print('Measurement.publish = ' + m.publish);
print('m.name = ' + m.name);
print('m.publish() = ' + m.publish());
print('m.type = ' + m.type);

var m2 = new Measurement();
print('m2.type = ' + m2.type);
print('m2.hitValue = ' + m2.hitValue);
