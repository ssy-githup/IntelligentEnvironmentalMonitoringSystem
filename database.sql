CREATE TABLE WeatherData (
     id BIGINT AUTO_INCREMENT PRIMARY KEY,
     humidity VARCHAR(255) NOT NULL,
     temperature VARCHAR(255) NOT NULL,
     pressure VARCHAR(255) NOT NULL,
     altitude VARCHAR(255) NOT NULL,
     avgTemp VARCHAR(255) NOT NULL,
     rainDetected VARCHAR(255) NOT NULL,
     timestamp DATETIME NOT NULL
);
