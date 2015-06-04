
var config = {'folder': '/tmp/pg'};
var p = new PerfGear(config);
print('PerfGear.start = ' + p.start());


var m = new Measurement('test/api/constructor');
print('m.name = ' + m.name);
m.hit();
print('m.hitValue = ' + m.hitValue);
print('m.publish() = ' + m.publish());

var m2 = new Measurement("test/api/save_timestamp");
m2.saveTimestamp();
m2.saveTimestamp();
m2.saveTimestamp();
print('m2.typeId = ' + m2.typeId);

m2.sequence.forEach(function(s, i) {
  print('m2.sequence['+i+'].timestamp = '+s.timestamp);
});

print('m2.publish() = ' + m2.publish());

p.stop();
