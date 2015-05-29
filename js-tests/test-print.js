print('hello from dukbridge')

print('PerfGear = ' + PerfGear);
var p = new PerfGear();
print('PerfGear.startPerfGear = ' + p.startPerfGear);

print('PGMeasurement = ' + PGMeasurement);

var m = new PGMeasurement('test');
print('PGMeasurement.publish = ' + m.publish);

print('m.publish() = ' + m.publish());
print('m.type = ' + m.type);

var m2 = new PGMeasurement();
print('m2.type = ' + m2.type);
