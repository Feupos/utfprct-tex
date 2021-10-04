;; Autoria: Gustavo Brunholi Chierici - Data 22/06/2021 - Grupo de Pesquisa: PON - UTFPR ;;

;;*******************************FUNÇÕES BÁSICAS**************************************;;

(defrecord FPSensor [is-read is-activated])     ;; Record ("struct") do sensor

(defn create-sensor [] (FPSensor. false false)) ;; Função que retorna um sensor

(defn activate-sensor                           ;; Função que "ativa" o sensor
    [sensor]
    (assoc sensor :is-activated true :is-read false))

(defn deactivate-sensor                         ;; Função que "desativa" o sensor
    [sensor]
    (assoc sensor :is-activated false))

(defn read-sensor                               ;; Função que "lê" o sensor
    [sensor]
    (assoc sensor :is-read true))

(defn check-sensor                              ;; Função que verifica se o sensor está ativado e o "lê" em caso positivo
    [sensor]
    (if (and (:is-activated sensor) (not (:is-read sensor)))
        (deactivate-sensor (read-sensor sensor)) sensor))

(defn print-sensor                              ;; Função para printar as informações do sensor
    [sensor]
    (println "Activated:" (:is-activated sensor) "- Read:" (:is-read sensor)))

;;***********************FUNÇÕES PARA TRABALHAR COM LISTAS***************************;;

(defn create-sensors                            ;; Função que retorna uma lista de FPSensors
    [number_of_sensors]
    (for [number (range number_of_sensors)]
        (create-sensor)))

(defn activate-sensors                          ;; Função que percorre uma lista de FPSensors, "ativando" eles, e devolve uma lista com FPSensors ativados
    [sensor_list]
    (for [sensor sensor_list]
        (activate-sensor sensor)))

(defn check-sensors                             ;; Função que percorre uma lista de FPSensors, verificando e, quando necessário, "lendo" eles, e devolve uma lista com FPSensors verificados
    [sensor_list]
    (for [sensor sensor_list]
        (check-sensor sensor)))

(defn print-sensors                             ;; Função que percorre uma lista de FPSensors e printa as informações de cada um
    [sensor_list]
    (doseq [sensor sensor_list]
        (print-sensor sensor)))

;;*******************************SUGESTÃO DE USO**************************************;;

(println "Criando sensores\n")
(def sensor-list (create-sensors 10))

(print-sensors sensor-list)

(println "\n**************************\n")
(println "\nAtivando sensores\n")

(def sensor-list (activate-sensors sensor-list))

(print-sensors sensor-list)

(println "\n**************************\n")
(println "\nVerificando sensores\n")

(def sensor-list (check-sensors sensor-list))

(print-sensors sensor-list)