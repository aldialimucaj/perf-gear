
var config = {'folder': '/tmp/pg_js', 'url':'http://localhost:3000/api/measurements'};
var p = new PerfGear(config);
print('PerfGear.start = ' + p.start());


var m = new Measurement('test/api/constructor');
print('m.name = ' + m.name);
m.hit();
print('m.hitValue = ' + m.hitValue);
print('m.publish() = ' + m.publish());
print('m.published ' + m.published);

var m2 = new Measurement("test/api/save_timestamp");
m2.saveTimestamp("Start");
m2.saveTimestamp("mid");
m2.saveTimestamp("End");


m2.sequence.forEach(function(s, i) {
  print('m2.sequence['+i+'].timestamp = '+s.timestamp);
});

print('m2.publish() = ' + m2.publish());
print('m2.published ' + m2.published);


var m3 = new Measurement("test/api/params");
m3.typeId = 1;
m3.test = "dynamic params";
print('m3.publish() = ' + m3.publish());
print('m3.published ' + m3.published);

var m4 = new Measurement("test/api/ram_usage");
m4.saveRamUsage();
m4.saveRamUsage();
m4.saveRamUsage();
print('m4.publish() = ' + m4.publish());
print('m4.published ' + m4.published);


p.stop();

