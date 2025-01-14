# influxdb-cxx-fork

This is a fork of the now archived influxdb access library written by https://github.com/awegrzyn/influxdb-cxx.git.

A large number of IoT applications rely on simple REST APIs with minimum requirements on the http implementation. 
The goal of this fork is to support such applications with a small footprint and self-contained influxdb client library by removing dependencies to boost and curl from the original library. 


InfluxDB C++ client library
 - Batch write
 - Data exploration
 - Supported embedded transports
   - HTTP with Basic Auth
   - UDP
 - Supported with external library dependencies
   - HTTPS with Basic Auth
   - Unix datagram socket


## Installation

 __Build requirements__
 - CMake 3.12+
 - C++17 compliler

 In CMakeLists.txt configure external library dependencies:
```bash
option(USE_CURL "Enable curl dependency" OFF)      # switch ON if you need https
option(USE_BOOST "Enable boost dependency" OFF)    # switch ON if you need Unix datagram sockets
```

### Generic
 ```bash
git clone https://github.com/ralfogit/influxdb-cxx-fork.git
cd influxdb-cxx-fork; mkdir build
cd build
cmake ..
sudo make install
 ```

### macOS
```bash
brew install awegrzyn/influxdata/influxdb-cxx
```

## Quick start

### Basic write

```cpp
// Provide complete URI
auto influxdb = influxdb::InfluxDBFactory::Get("http://localhost:8086/?db=test");
influxdb->write(Point{"test"}
  .addField("value", 10)
  .addTag("host", "localhost")
);
```

### Batch write

```cpp
// Provide complete URI
auto influxdb = influxdb::InfluxDBFactory::Get("http://localhost:8086/?db=test");
// Write batches of 100 points
influxdb->batchOf(100);

for (;;) {
  influxdb->write(Point{"test"}.addField("value", 10));
}
```

### Query

```cpp
// Available over HTTP only
auto influxdb = influxdb::InfluxDBFactory::Get("http://localhost:8086/?db=test");
/// Pass an IFQL to get list of points
std::vector<Point> points = idb->query("SELECT * FROM test");
```

## Transports

An underlying session protocol is fully configurable by passing an URI:
```
[protocol]://[username:password@]host:port[/?db=database]
```
<br>
List of supported protocols:

| Name                 | Dependency               | URI protocol   | Sample URI                        |
| ---------------------|:------------------------:|:--------------:|:----------------------------------|
| HTTP                 | none                     | `http`         | `http://localhost:8086/?db=<db>`  |
| UDP                  | none                     | `udp`          | `udp://localhost:8094`            |
| HTTPS                | libcurl,libssl,libcrypto | `https`        | `https://localhost:8086/?db=<db>` |
| Unix datagram socket | boost                    | `unix`         | `unix:///tmp/telegraf.sock`       |

