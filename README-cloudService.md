# Spring Boot Project Dependencies and Configuration

To set up a Spring Boot project for the scenario you described, you'll need to include several dependencies and configure the application properties. Below is a guide on how to do that.

## 1. Project Dependencies

In a Maven-based Spring Boot project, dependencies are defined in the `pom.xml` file. Here’s what you need to include:

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.hope</groupId>
    <artifactId>sensor-data-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.6</version> <!-- Change this to the latest stable version -->
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

    <dependencies>
        <!-- Spring Boot Web dependency -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <!-- Spring Boot Data JPA dependency -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jpa</artifactId>
        </dependency>

        <!-- MySQL Connector Java dependency -->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <scope>runtime</scope>
        </dependency>

        <!-- Spring Boot Starter Test dependency -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
</project>
```

# Database connection settings
spring.datasource.url=jdbc:mysql://localhost:3306/your_database_name?useSSL=false&serverTimezone=UTC
spring.datasource.username=your_username
spring.datasource.password=your_password

## JPA/Hibernate settings
spring.jpa.hibernate.ddl-auto=update
spring.jpa.show-sql=true

## Optional: You can change the dialect if necessary
spring.jpa.properties.hibernate.dialect=org.hibernate.dialect.MySQL8Dialect

## Server port (optional, default is 8080)
server.port=8080

# Main Application Class
```css
src
└── main
    ├── java
    │   └── com
    │       └── example
    │           ├── controller
    │           │   └── MyController.java
    │           ├── service
    │           │   └── MyService.java
    │           ├── service
    │           │   └── MyServiceImpl.java
    │           ├── repository
    │           │   └── MyRepository.java
    │           ├── model
    │           │   └── MyEntity.java
    │           └── MyApplication.java
    └── resources
        └── application.properties


```

Ensure you have a main application class to bootstrap your Spring Boot application:
```
package com.hope;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class SensorDataAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(SensorDataAppApplication.class, args);
    }
}

```
WeatherData.java
```java
package com.hope.model;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;

@Entity
public class WeatherData {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String humidity;
    private String temperature;
    private String pressure;
    private String altitude;
    private String avgTemp;
    private String rainDetected;
    private LocalDateTime timestamp;

    // Getters and Setters

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getHumidity() {
        return humidity;
    }

    public void setHumidity(String humidity) {
        this.humidity = humidity;
    }

    public String getTemperature() {
        return temperature;
    }

    public void setTemperature(String temperature) {
        this.temperature = temperature;
    }

    public String getPressure() {
        return pressure;
    }

    public void setPressure(String pressure) {
        this.pressure = pressure;
    }

    public String getAltitude() {
        return altitude;
    }

    public void setAltitude(String altitude) {
        this.altitude = altitude;
    }

    public String getAvgTemp() {
        return avgTemp;
    }

    public void setAvgTemp(String avgTemp) {
        this.avgTemp = avgTemp;
    }

    public String getRainDetected() {
        return rainDetected;
    }

    public void setRainDetected(String rainDetected) {
        this.rainDetected = rainDetected;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }
}

```
WeatherDataRepository.java
```java
package com.hope.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import com.hope.model.WeatherData;

public interface WeatherDataRepository extends JpaRepository<WeatherData, Long> {
}

```
WeatherDataService.java
```java
package com.hope.service;

import com.hope.model.WeatherData;

public interface WeatherDataService {
    WeatherData saveWeatherData(WeatherData weatherData);
}
```
WeatherDataServiceImpl.java
```java
package com.hope.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.hope.model.WeatherData;
import com.hope.repository.WeatherDataRepository;

@Service
public class WeatherDataServiceImpl implements WeatherDataService {

    @Autowired
    private WeatherDataRepository weatherDataRepository;

    @Override
    public WeatherData saveWeatherData(WeatherData weatherData) {
        return weatherDataRepository.save(weatherData);
    }
}
```
SystemController.java
```java
package com.hope.controller;

import com.hope.model.WeatherData;
import com.hope.service.WeatherDataService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

@RestController
@RequestMapping("/data")
public class SystemController {

    @Autowired
    private WeatherDataService weatherDataService;

    @PostMapping("/data")
    public ResponseEntity<String> receiveData(
            @RequestParam("humidity") String humidity,
            @RequestParam("temperature") String temperature,
            @RequestParam("pressure") String pressure,
            @RequestParam("altitude") String altitude,
            @RequestParam("avgTemp") String avgTemp,
            @RequestParam("rainDetected") String rainDetected) {

        // 获取当前时间并格式化
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String formattedNow = now.format(formatter);

        // 打印接收到的数据在同一行
        System.out.println(formattedNow + " | Humidity: " + humidity +
                " | Temperature: " + temperature +
                " | Pressure: " + pressure +
                " | Altitude: " + altitude +
                " | Average Temperature: " + avgTemp +
                " | Rain Detected: " + rainDetected
        );

        // 创建 WeatherData 对象并设置属性
        WeatherData weatherData = new WeatherData();
        weatherData.setHumidity(humidity);
        weatherData.setTemperature(temperature);
        weatherData.setPressure(pressure);
        weatherData.setAltitude(altitude);
        weatherData.setAvgTemp(avgTemp);
        weatherData.setRainDetected(rainDetected);
        weatherData.setTimestamp(now);

        // 使用 Service 保存数据到数据库
        weatherDataService.saveWeatherData(weatherData);

        // 返回响应
        return ResponseEntity.ok("Data received and saved successfully");
    }
}

```
application.properties
```properties
spring.datasource.url=jdbc:mysql://localhost:3306/your_database_name
spring.datasource.username=your_username
spring.datasource.password=your_password
spring.jpa.hibernate.ddl-auto=update
spring.jpa.show-sql=true

```
# database.sql
