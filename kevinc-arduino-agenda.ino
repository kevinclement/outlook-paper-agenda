#include <WiFi.h>
#include <HTTPClient.h>
#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include "AgendaParser.h"

JsonStreamingParser parser;
ExampleListener listener;

const char* ssid = "Kevin";
const char* password =  "henry123";

 // openssl s_client -connect outlook-sdf.office.com:443 -showcerts
const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIEkjCCA3qgAwIBAgIQAZ7Bxr0/WXuyDDM45VHYdzANBgkqhkiG9w0BAQsFADBh\n" \
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
"QTAeFw0xNTA4MDQxMjAwMDBaFw0zMDA4MDQxMjAwMDBaMEsxCzAJBgNVBAYTAlVT\n" \
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxJTAjBgNVBAMTHERpZ2lDZXJ0IENsb3Vk\n" \
"IFNlcnZpY2VzIENBLTEwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDR\n" \
"rfaHFHlUJ1fHLwVoPJs8zWfsRRAshPKkR8TZU0JFCbvk/jPB17xGL9GL5re1Z3h8\n" \
"anC+/bjltlTPTF6suCJ0c1UpCHPIZPfQlQkOeYNQv1/11MybQmGOgAS5QarOThKZ\n" \
"m6zWxb5bAnO1FqSrcWLUmOpAOYWm9rsv6OeHwov2nDLN7Pg+v4nndCOCS9rqv3Om\n" \
"JTz9v6nlaP/4MKJgxzsuo/PFfzs7/Q8xoXx0D9C/FMS9aPGl52un35sAfkYlTubo\n" \
"E/P2BsfUbwsnIEJdYbw/YNJ8lnLJfLCL//lIBVME+iKvt81RXW3dkHQD8DNP9MfA\n" \
"PlZGR69zIIvcej6j8l3/AgMBAAGjggFaMIIBVjASBgNVHRMBAf8ECDAGAQH/AgEA\n" \
"MA4GA1UdDwEB/wQEAwIBhjA0BggrBgEFBQcBAQQoMCYwJAYIKwYBBQUHMAGGGGh0\n" \
"dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTB7BgNVHR8EdDByMDegNaAzhjFodHRwOi8v\n" \
"Y3JsNC5kaWdpY2VydC5jb20vRGlnaUNlcnRHbG9iYWxSb290Q0EuY3JsMDegNaAz\n" \
"hjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRHbG9iYWxSb290Q0Eu\n" \
"Y3JsMD0GA1UdIAQ2MDQwMgYEVR0gADAqMCgGCCsGAQUFBwIBFhxodHRwczovL3d3\n" \
"dy5kaWdpY2VydC5jb20vQ1BTMB0GA1UdDgQWBBTdUdCiMXOpc66PtAF+XYxXy5/w\n" \
"9zAfBgNVHSMEGDAWgBQD3lA1VtFMu2bwo+IbG8OXsj3RVTANBgkqhkiG9w0BAQsF\n" \
"AAOCAQEACCnEyKb+tDgo96MZZ4zqBTsOS0BiYh48FMYF3DanTzJxRgVegB1ca/Bt\n" \
"bdkhdgu9RsS5ZpdN/4AUeodphLLW/8kWcL6jzIshre5cjSStwo+Z4MyeigkDuA+a\n" \
"tVuQKyr316UvSmWoxOTFx3GplkZPq21LKhbL8ak79h8hObTrrWAEgpsSv96r0kYd\n" \
"DA07dgL5C9XOU4VCeylNRtGLzWTsIRZPLwFDWNFl7Vyl+0Sg0lDo3mbEtjGehzMD\n" \
"sMnGSxLnWzWU2UbOMeu/uPaeC4SFgiJWxCOEVOdSMwwlyxrsRFUPY5Zys80ZXn4O\n" \
"J4XVpOqw4qXcBiklkOjOLOnp0Hzvzg==\n" \
"-----END CERTIFICATE-----\n";

void setup() {
 
  Serial.begin(115200);
  delay(1000);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
    http.setConnectTimeout(60000);
    http.setTimeout(60000);
 
    http.begin("https://outlook.office365.com/owa/calendar/f4afdfc98d304e2b8a58b0740090888d@microsoft.com/42c618b2217d434688e749ff0cf238c115819208843645457799/service.svc", root_ca);

    http.addHeader("Action", "FindItem");
    
    String payload_body = "{\"__type\":\"FindItemJsonRequest:#Exchange\",\"Header\":{\"__type\":\"JsonRequestHeaders:#Exchange\",\"RequestServerVersion\":\"Exchange2013\",\"TimeZoneContext\":{\"__type\":\"TimeZoneContext:#Exchange\",\"TimeZoneDefinition\":{\"__type\":\"TimeZoneDefinitionType:#Exchange\",\"Id\":\"Pacific Standard Time\"}}},\"Body\":{\"__type\":\"FindItemRequest:#Exchange\",\"ItemShape\":{\"__type\":\"ItemResponseShape:#Exchange\",\"BaseShape\":\"IdOnly\",\"AdditionalProperties\":[{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"ItemParentId\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"Sensitivity\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"AppointmentState\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsCancelled\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"HasAttachments\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"LegacyFreeBusyStatus\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"CalendarItemType\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"Start\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"End\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsAllDayEvent\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"Organizer\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"Subject\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsMeeting\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"UID\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"InstanceKey\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"ItemEffectiveRights\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"JoinOnlineMeetingUrl\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"ConversationId\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"CalendarIsResponseRequested\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"Categories\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsRecurring\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsOrganizer\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"EnhancedLocation\"},{\"__type\":\"PropertyUri:#Exchange\",\"FieldURI\":\"IsSeriesCancelled\"}]},\"ParentFolderIds\":[{\"__type\":\"FolderId:#Exchange\",\"Id\":\"AAMkAGY0YWZkZmM5LThkMzAtNGUyYi04YTU4LWIwNzQwMDkwODg4ZAAuAAAAAAAinpXKstMcRIsDKoPjzoxSAQDYeirqiu/aQrXjfEsmxranAAAAj87EAAA=\",\"ChangeKey\":\"AgAAAA==\"}],\"Traversal\":\"Shallow\",\"Paging\":{\"__type\":\"CalendarPageView:#Exchange\",\"StartDate\":\"2019-06-30T00:00:00.001\",\"EndDate\":\"2019-08-04T00:00:00.000\"}}}";
    
    int httpCode = http.POST(payload_body); 
 
    if (httpCode > 0) { //Check for the returning code        
        int len = http.getSize();
        Serial.printf("SUCCESS!\n");
        Serial.printf("  code: %d\n", httpCode);
        Serial.printf("  size: %d\n", len);

        uint8_t buff[128] = { 0 };
        WiFiClient * stream = http.getStreamPtr();

        Serial.printf("Starting parse with heap size: %d\n", String(ESP.getFreeHeap()));
        parser.setListener(&listener);

        while(http.connected() && (len > 0 || len == -1)) {
          // get available data size
          size_t size = stream->available();

          if(size) {
            // read up to 128 byte
            int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
            for(int jj = 0; jj<c; jj++) {
              parser.parse(buff[jj]); 
            }

            if(len > 0) {
              len -= c;
            }
          }
          delay(1);
        }

        Serial.printf("Finished parse with heap size: %d\n", String(ESP.getFreeHeap()));
      }
 
    else {
      Serial.println("Error on HTTP request");
      Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
 
    http.end(); //Free the resources
  }
}
 
void loop() {
 
//  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
// 
//    HTTPClient http;
// 
//    http.begin("https://outlook-sdf.office.com/", root_ca);
//    int httpCode = http.GET();
// 
//    if (httpCode > 0) { //Check for the returning code
// 
//        String payload = http.getString();
//        Serial.println(httpCode);
//        Serial.println(payload);
//      }
// 
//    else {
//      Serial.println("Error on HTTP request");
//    }
// 
//    http.end(); //Free the resources
//  }
// 
//  delay(10000);
}