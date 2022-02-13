#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <fstream>
#include <sstream>

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  
  ENDPOINT("POST", "/", postUsers, BODY_STRING(String, userInfo)) {

    OATPP_LOGD("POST", "body='%.10s'", userInfo->c_str());

    std::ofstream out("scene.xml");
    out << userInfo->c_str();
    out.close();

    auto dto = MyDto::createShared();

    system("../../rt/rt ./scene.xml ./picture.bmp");
    system("base64 ./picture.bmp -o ./picture.base64");

    std::ifstream t("picture.base64");
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    dto->statusCode = 200;
    dto->message = buffer.str();

    auto response = createDtoResponse(Status::CODE_200, dto);
    response->putHeader("Access-Control-Allow-Origin", "*");
    return response;
  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
