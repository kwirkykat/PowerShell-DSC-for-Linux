#!/bin/sh

# $0 ADD_JSON CurrentReport PropertyName PropertyValue
# $0 SEND_REPORT JobId OperationType RefreshMode Status ReportFormatVersion ConfigurationVersion StartTime EndTime RebootRequested StatusData[] Errors[] AdditionalData[]

curDate=`date +%Y-%m-%dT%T.%N%:z`
ErrorMessage=""
Errors=""
RNIDS=""

IPV4Addresses="IP1"
IPV6Addresses="IP2"

: <<'END'
IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";" | cut -c 1-254`
if [[ $IPAddress == *[.]* ]]; then
    IPV4Addresses= $IPAddress
else
    IPV6Addresses = $IPAddress
fi


if [ "$2" = "EndTime" ]; then
    if [ -n "$3" ]; then
        ErrorMessage="\"{\\\"Locale\\\":\\\"en-US\\\",\\\"ErrorCode\\\":\\\"1\\\",\\\"ErrorMessage\\\":\\\"$3\\\",\\\"ResourceId\\\":\\\"DSCEngine\\\",\\\"ErrorSource\\\":\\\"DSCEngine\\\"}\""
        Errors=",\\\"Error\\\":\\\"$3\\\""
        if [ -n "${14}" ]; then
            RNIDS="{\\\"ReportFormatVersion\\\":\\\"2.1\\\",\\\"SourceInfo\\\":\\\"$4\\\",\\\"ModuleName\\\":\\\"$5\\\",\\\"DurationInSeconds\\\":\\\"0\\\",\\\"InstanceName\\\":\\\"$7\\\",\\\"StartDate\\\":\\\"$curDate\\\",\\\"ResourceName\\\":\\\"$9\\\",\\\"ModuleVersion\\\":\\\"${10}\\\",\\\"RebootRequested\\\":\\\"${11}\\\",\\\"ResourceId\\\":\\\"${12}\\\",\\\"ConfigurationName\\\":\\\"${13}\\\",\\\"InDesiredState\\\":\\\"${14}\\\"}"
        else
            RNIDS="{\\\"ReportFormatVersion\\\":\\\"2.2\\\",\\\"SourceInfo\\\":\\\"(null)\\\",\\\"ModuleName\\\":\\\"PsDesiredStateConfiguration\\\",\\\"DurationInSeconds\\\":\\\"0\\\",\\\"InstanceName\\\":\\\"LCM\\\",\\\"StartDate\\\":\\\"$curDate\\\",\\\"ResourceName\\\":\\\"(null)\\\",\\\"ModuleVersion\\\":\\\"1.1\\\",\\\"RebootRequested\\\":\\\"False\\\",\\\"ResourceId\\\":\\\"[DSC]LCM\\\",\\\"ConfigurationName\\\":\\\"(null)\\\",\\\"InDesiredState\\\":\\\"False\\\"}"
        fi
        output="{\"JobId\":\"$1\",\"ConfigurationVersion\":\"2.0.0\",\"ReportFormatVersion\":\"2.3\",\"LCMVersion\":\"2.0\",\"EndTime\":\"$curDate\",\"Errors\":[$ErrorMessage],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\",\\\"ResourcesNotInDesiredState\\\":[$RNIDS]$Errors}\"]}"
    else
        output="{\"JobId\":\"$1\",\"ConfigurationVersion\":\"2.0.0\",\"ReportFormatVersion\":\"2.4\",\"LCMVersion\":\"2.0\",\"EndTime\":\"$curDate\",\"Errors\":[$ErrorMessage],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"]}"
    fi
else
    IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";" | cut -c 1-254`
    output="{\"JobId\":\"$1\",\"OperationType\":\"Consistency\",\"NodeName\":\"${15}\",\"IpAddress\":\"$IPAddress\",\"ReportFormatVersion\":\"2.5\",\"LCMVersion\":\"2.0\",\"StartTime\":\"$curDate\",\"Errors\":[],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"]}"

fi

echo $output > <CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>/last_statusreport
echo $output

END
output="{\"JobId\":\"$2\", \"OperationType\":\"$3\", \"RefreshMode\":\"$4\", \"Status\":\"$5\", \"ReportFormatVersion\":\"$6\", \"ConfigurationVersion\":\"$7\", \"StartTime\":\"$8\", \"EndTime\":\"$9\", \"RebootRequested\":\"${10}\", \"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"], \"Errors\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"], \"AdditionalData\":[]}"
echo $output > <CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>/last_statusreport
echo $output