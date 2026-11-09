#ifndef FAULTSIM_TYPES_H
#define FAULTSIM_TYPES_H

#include <stdint.h>

/* Union used for engine fault simulation */
typedef union
{
    /* The variable below recieves the fault bits */
    uint64_t FaultBits;
   
   struct Faults
   {

       /* SENSOR FAILURES */

       /*Ts2 sensor 1 possible faults - Bits 0 to 2*/
       uint64_t Ts2_0_SCV       :1;
       uint64_t Ts2_0_SCG       :1;
       uint64_t Ts2_0_Open      :1;
       
       /*Ts2 sensor 2 possible faults - Bits 3 to 5*/
       uint64_t Ts2_1_SCV       :1;
       uint64_t Ts2_1_SCG       :1;
       uint64_t Ts2_1_Open      :1;
       
       /*Pt3 sensor 1 possible faults - Bits 6 to 7*/
       uint64_t Pt3_0_Short     :1;
       uint64_t Pt3_0_Open      :1;
       
       /*Tt4 sensor 1 possible faults - Bits 8 to 10*/
       uint64_t Tt4_0_SCV       :1;
       uint64_t Tt4_0_SCG       :1;
       uint64_t Tt4_0_Open      :1;
       
       /*Tt4 sensor 2 possible faults - Bits 11 to 13*/
       uint64_t Tt4_1_SCV       :1;
       uint64_t Tt4_1_SCG       :1;
       uint64_t Tt4_1_Open      :1;
       
       /*Tt4 sensor 3 possible faults - Bits 14 to 16*/
       uint64_t Tt4_2_SCV       :1;
       uint64_t Tt4_2_SCG       :1;
       uint64_t Tt4_2_Open      :1;
       
       /*RPM sensor 1 possible faults - Bits 17 to 20*/
       uint64_t RPM_0_Short     :1;
       uint64_t RPM_0_Open      :1;
       uint64_t RPM_0_1PLoss    :1;
       uint64_t RPM_0_2PLoss    :1;
       
       /*RPM sensor 2 possible faults - Bits 21 to 24*/
       uint64_t RPM_1_Short     :1;
       uint64_t RPM_1_Open      :1;
       uint64_t RPM_1_1PLoss    :1;
       uint64_t RPM_1_2PLoss    :1;
       
      /*POil sensor 1 possible faults - Bits 25 to 26*/
       uint64_t POil_0_Short    :1;
       uint64_t POil_0_Open     :1;
       
       /* PFuel sensor 1 possible faults - Bits 27 to 28*/
       uint64_t PFuel_0_Short   :1;
       uint64_t PFuel_0_Open    :1;
       
       /* Vibration sensor 1 possible faults - Bits 29 to 30*/
       uint64_t Vib_0_Short     :1;
       uint64_t Vib_0_Open      :1;

       /* SYSTEM FAILURES */
       
       /* Lubrication system faults - Bits 31 to 32*/
       uint64_t POil_High       :1;
       uint64_t POil_Low        :1;
       
       /* Fuel system faults - Bits 33 to 34 */
       uint64_t PFuel_High      :1;
       uint64_t PFuel_Low       :1;

       /* Engine Blowout - Bit 35 */
       uint64_t BlowOut         :1;
       
       /* Mec system faults - Bits 36 to 40*/
       uint64_t VibrationHigh   :1;
       uint64_t Mec_Lock        :1;
       uint64_t OverTemp        :1;
       uint64_t OverSpeed       :1;
       uint64_t Ignition        :1;

       /* Sensors bias - Bits 41 to 51 */
       uint64_t Ts2_0_Bias      :1;
       uint64_t Ts2_1_Bias      :1;
       uint64_t Pt3_0_Bias      :1;
       uint64_t Tt4_0_Bias      :1;
       uint64_t Tt4_1_Bias      :1;
       uint64_t Tt4_2_Bias      :1;
       uint64_t RPM_0_Bias      :1;
       uint64_t RPM_1_Bias      :1;
       uint64_t POil_0_Bias     :1;
       uint64_t PFuel_0_Bias    :1;
       uint64_t Vib_0_Bias      :1;

       /* Bit indicating that thermocouple faults are simulated by software - Bit 52 */
       /* The float number MATLAB is able to work with must contain 53 bits or less.
       Therefore, the position of TCFaultSoftSim was placed at bit 52 (last bit 
       countig from 0)  */
       uint64_t TCFaultSoftSim  :1;

       /* TBear 0 sensor possible faults - Bit 53 */
       uint64_t TB_0_Open       :1;
       /* TBear 1 sensor possible faults - Bit 54 */
       uint64_t TB_1_Open       :1;
       /* TBear 2 sensor possible faults - Bit 55 */
       uint64_t TB_2_Open       :1;

       /* Bearing overtemp - Bits 56 to 58 */
       uint64_t TBear_0_High    :1;
       uint64_t TBear_1_High    :1;
       uint64_t TBear_2_High    :1;

       /* CAN network - Bits 59 to 60 */
       uint64_t CAN_0_Fault     :1;
       uint64_t CAN_1_Fault     :1;

       /* Reserved bits - Bits 61 to 63 */
       uint64_t NotUsedBits     :3;
       
   } Faults;
   
} EngineFaults;

/* Union for informing final state of sensor faults */
typedef union
{

    uint64_t FaultBits;
    
   struct
   {

       /*Ts2 sensor 1 possible faults - Bits 0 to 2*/
       uint64_t Ts2_0_SCV       :1;
       uint64_t Ts2_0_SCG       :1;
       uint64_t Ts2_0_Open      :1;
       
       /*Ts2 sensor 2 possible faults - Bits 3 to 5*/
       uint64_t Ts2_1_SCV       :1;
       uint64_t Ts2_1_SCG       :1;
       uint64_t Ts2_1_Open      :1;
       
       /*Pt3 sensor 1 possible faults - Bits 6 to 7*/
       uint64_t Pt3_0_Short     :1;
       uint64_t Pt3_0_Open      :1;
       
       /*Tt4 sensor 1 possible faults - Bits 8 to 10*/
       uint64_t Tt4_0_SCV       :1;
       uint64_t Tt4_0_SCG       :1;
       uint64_t Tt4_0_Open      :1;
       
       /*Tt4 sensor 2 possible faults - Bits 11 to 13*/
       uint64_t Tt4_1_SCV       :1;
       uint64_t Tt4_1_SCG       :1;
       uint64_t Tt4_1_Open      :1;
       
       /*Tt4 sensor 3 possible faults - Bits 14 to 16*/
       uint64_t Tt4_2_SCV       :1;
       uint64_t Tt4_2_SCG       :1;
       uint64_t Tt4_2_Open      :1;
       
       /*RPM sensor 1 possible faults - Bits 17 to 20*/
       uint64_t RPM_0_Short     :1;
       uint64_t RPM_0_Open      :1;
       uint64_t RPM_0_PLoss1    :1;
       uint64_t RPM_0_PLoss2    :1;
       
       /*RPM sensor 2 possible faults - Bits 21 to 24*/
       uint64_t RPM_1_Short     :1;
       uint64_t RPM_1_Open      :1;
       uint64_t RPM_1_PLoss1    :1;
       uint64_t RPM_1_PLoss2    :1;
       
      /*POil sensor 1 possible faults - Bits 25 to 26*/
       uint64_t POil_0_Short    :1;
       uint64_t POil_0_Open     :1;
       
       /* PFuel sensor 1 possible faults - Bits 27 to 28*/
       uint64_t PFuel_0_Short   :1;
       uint64_t PFuel_0_Open    :1;
       
       /* Vibration sensor 1 possible faults - Bits 29 to 30*/
       uint64_t Vib_0_Short     :1;
       uint64_t Vib_0_Open      :1;

       /* Bearing 0 Thermocouple Faults - Bit 31 */
       uint64_t TB_0_Open       :1;
       /* Bearing 1 Thermocouple Faults - Bit 32 */
       uint64_t TB_1_Open       :1;
       /* Bearing 2 Thermocouple Faults - Bit 33 */
       uint64_t TB_2_Open       :1;

       /* Reserved bits */
       uint64_t Reserved        :28;

   } SensFaults;
    
}SensorFaults;

/* Union informing at which sensor a hard fault has been detected
as well as which system faults have been detected */
typedef union
{

    uint64_t FaultBits;
    
   struct DetFault
   {

       /* SENSOR FAULTS */

       /*Ts2 sensor 0 possible faults - Bit 0 */
       uint64_t Ts2_0_Fault       :1;
       /*Ts2 sensor 1 possible faults - Bit 1 */
       uint64_t Ts2_1_Fault       :1;
       /*Pt3 sensor 0 possible faults - Bit 2 */
       uint64_t Pt3_0_Fault       :1;
       /*Tt4 sensor 0 possible faults - Bit 3 */
       uint64_t Tt4_0_Fault       :1;
       /*Tt4 sensor 1 possible faults - Bit 4 */
       uint64_t Tt4_1_Fault       :1;
       /*Tt4 sensor 2 possible faults - Bit 5 */
       uint64_t Tt4_2_Fault       :1;
       /*RPM sensor 0 possible faults - Bit 6 */
       uint64_t RPM_0_Fault       :1;
       /*RPM sensor 1 possible faults - Bit 7 */
       uint64_t RPM_1_Fault       :1;
       /*POil sensor 0 possible faults - Bit 8 */
       uint64_t POil_0_Fault      :1;
       /* PFuel sensor 0 possible faults - Bit 9 */
       uint64_t PFuel_0_Fault     :1;
       /* Vibration sensor 0 possible faults - Bit 10 */
       uint64_t Vib_0_Fault       :1;
       /*Bearing temperature sensor 0 possible faults - Bit 11 */
       uint64_t TB_0_Fault       :1;
       /*Bearing temperature sensor 1 possible faults - Bit 12 */
       uint64_t TB_1_Fault       :1;
       /*Bearing temperature sensor 2 possible faults - Bit 13 */
       uint64_t TB_2_Fault	     :1;

       /* SYSTEM FAILURES */
       
       /* Lubrication system faults - Bits 14 to 15*/
       uint64_t POil_High       :1;
       uint64_t POil_Low        :1;
       
       /* Fuel system faults - Bits 16 to 17 */
       uint64_t PFuel_High      :1;
       uint64_t PFuel_Low       :1;

       /* Engine Blowout - Bit 18 */
       uint64_t BlowOut         :1;
       
       /* Mec system faults - Bits 19 to 23*/
       uint64_t VibrationHigh   :1;
       uint64_t Mec_Lock        :1;
       uint64_t OverTemp        :1;
       uint64_t OverSpeed       :1;
       uint64_t Ignition        :1;

       /* Bearing 0 fault - Bit 24 */
       uint64_t TB_0_High : 1;
       /* Bearing 1 fault - Bit 25 */
       uint64_t TB_1_High : 1;
       /* Bearing 2 fault - Bit 26 */
       uint64_t TB_2_High : 1;

        /* CAN network - Bits 27 to 28 */
       uint64_t CAN_0_Fault     :1;
       uint64_t CAN_1_Fault     :1;

       /* Reserved bits */
       uint64_t Reserved          :35;

   } DetFaults;
    
}FaultDetect;

/* Union containing the bits map of thermocouple fault for current CI */
typedef union
{
    /* int containing all bits */
    uint8_t TCFaultBits;
    
    /* struct containing individual bits */
    struct 
    {
        
       /*Ts2 sensor 1 possible faults*/
       uint64_t OC            :1;
       uint64_t SCG           :1;
       uint64_t SCV           :1;
       uint64_t AnyFault      :1;
       uint64_t Reserved      :4;
        
    }Faults;
        
}TCFaults;

/* Union informing the what system failures has been detected at each sensor */
typedef union
{
    /* int containing all bits */
    uint64_t FaultBits;
    
    /* struct containing individual bits */
    struct 
    {
        
       /*Pt3 sensor 0 system faults - Bits 0 to 1*/
       uint64_t Pt3_0_BlowOut         :1;
       uint64_t Pt3_0_MecLock         :1;
       
       /*Tt4 sensor 0 system faults - Bits 2 to 4*/
       uint64_t Tt4_0_High            :1;
       uint64_t Tt4_0_BlowOut         :1;
       uint64_t Tt4_0_MecLock         :1;
       
       /*Tt4 sensor 1 system faults - Bits 5 to 7*/
       uint64_t Tt4_1_High            :1;
       uint64_t Tt4_1_BlowOut         :1;
       uint64_t Tt4_1_MecLock         :1;
       
       /*Tt4 sensor 2 system faults - Bits 8 to 10*/
       uint64_t Tt4_2_High            :1;
       uint64_t Tt4_2_BlowOut         :1;
       uint64_t Tt4_2_MecLock         :1;
       
       /*RPM sensor 0 system faults - Bits 11 to 13*/
       uint64_t RPM_0_High            :1;
       uint64_t RPM_0_BlowOut         :1;
       uint64_t RPM_0_MecLock         :1;
       
       /*RPM sensor 1 system faults - Bits 14 to 16*/
       uint64_t RPM_1_High            :1;
       uint64_t RPM_1_BlowOut         :1;
       uint64_t RPM_1_MecLock         :1;   
       
       /* POil sensor 0 system faults - Bits 17 to 18*/
       uint64_t POil_0_High           :1;
       uint64_t POil_0_Low            :1;
       
       /* PFuel sensor 0 system faults - Bits 19 to 20*/
       uint64_t PFuel_0_High          :1;
       uint64_t PFuel_0_Low           :1;
       
       /* Vibration sensor 0 system faults - Bit 21 */
       uint64_t Vib_0_High            :1;

       /* Bearing 0 Thermocouple Faults - Bit 22 */
       uint64_t TB_0_High : 1;
       /* Bearing 1 Thermocouple Faults - Bit 23 */
       uint64_t TB_1_High : 1;
       /* Bearing 2 Thermocouple Faults - Bit 24 */
       uint64_t TB_2_High : 1;

       /* CAN network - Bits 25 to 26 */
       uint64_t CAN_0_Fault     :1;
       uint64_t CAN_1_Fault     :1;

       /* Ignition - Bit 27 */
       uint64_t Ignition        :1;

       /* Reserved bits - Bits 28 to 63*/
       uint64_t Reserved : 36;

    }SysFaults;
        
}SystemFaults;

typedef union
{
    /* Word indicating sensed pars  */
    uint64_t ModParsBits;
    
    /* data */
    struct 
    {
        /* STATION 2 */
        
        uint64_t Ts2    :1;

        /* STATION 3 */
        
        uint64_t Pt3    :1;

        /* STATION 4 */
        
        uint64_t Tt4    :1;

        /* SHAFT */
        
        uint64_t RPM    :1;


    }ModelPars;

}ModelParsFault;

/* Union informing the what system failures has been detected at each sensor */
typedef union
{
    /* int containing all bits */
    uint64_t EngineStatus;
    
    /* struct containing individual bits */
    struct 
    {
        
       /* Engine state bits - Bits 0 to 10 */
       uint64_t Initialize           :1;
       uint64_t Windmilling          :1;
       uint64_t ReadyToStart         :1;
       uint64_t Starting             :1;
       uint64_t Idle                 :1;
       uint64_t Regime               :1;
       uint64_t ShutOff              :1;
       uint64_t Emergency            :1;
       uint64_t Fail                 :1;
       uint64_t Degraded             :1;
       
       /* Reserved bits - Bits 11 to 63*/
       uint64_t Reserved              :54;
        
    }EngStatusBist;
        
}EngineStatus;

#endif /* FAULTSIM_TYPES_H */
