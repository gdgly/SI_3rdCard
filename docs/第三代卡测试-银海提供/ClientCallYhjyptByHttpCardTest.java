package test;

import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.Iterator;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.jdom.Element;
import org.jdom.input.SAXBuilder;



public class ClientCallYhjyptByHttpCardTest {
	
	@SuppressWarnings("deprecation")
	public static void main(String[] args) throws Exception { 
		int t1=(int) System.currentTimeMillis();
		String inputxml="<input><keyword>510100|0081544C968684510100035676|03|510100D156000005F0348866E075C174|C49031D2A31E6A14|0102030405060708|096D1FFE340D812F|0102030405060708|HDOS1001120170609320000000000000</keyword><aab301>510100</aab301><zdbm>DCKJ0100201706014606000000000000</zdbm></input>";
    	
	    String testUrl="https://od.cdhrss.gov.cn:8045/yhjypt/services/yinHaiBusiness?wsdl";
	    String returnxml = httpPostCallBusiness(inputxml,testUrl,"0002","0002test","cdsi0000047");
    	System.out.println(returnxml);
    	int t2=(int) System.currentTimeMillis();
    	System.out.println(t2-t1);
	}   
	
	
	/**
     * 以httppost的方式调用平台的callBusiness方法 
     * @return
	 * @throws Exception 
     */
	@SuppressWarnings("unchecked")
	public static String httpPostCallBusiness(String inputXml,String webAddress,String username,String password,String funNo) throws Exception {
		CloseableHttpClient httpclient = HttpClients.createDefault();
		String returnxml = "";
        try {
	   	    HttpPost httppost = new HttpPost(webAddress);//内网地址 
	   	    httppost.setHeader("Content-Type", "application/soap+xml; charset=utf-8");
	   	    String callbusinessXml = getCallBusinessReqXml(username,password,inputXml,funNo);
	   		// 设置请求的数据
	   		StringEntity httppostEntity = new StringEntity(callbusinessXml,"UTF-8");
	   		httppostEntity.setContentType("text/xml; charset=utf-8");
	   		httppost.setEntity(httppostEntity);
	   		// 执行
	   		CloseableHttpResponse response = httpclient.execute(httppost);
	   		HttpEntity entity = response.getEntity();
	   		//返回结果处理
	   		try {  
                if (entity != null) { 
                	returnxml = getReturnXml(EntityUtils.toString(entity, "UTF-8"));
                }else {
                	returnxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><result><code>-1</code><message>没有获取到平台返回的内容!</message></result>";
				}  
            } finally {  
                response.close();  
            }  
        } catch (Exception e) {
        	returnxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><result><code>-1</code><message>"+e.getMessage()+"</message></result>";
        } finally {  
            // 关闭连接,释放资源    
            try {  
                httpclient.close();  
            } catch (IOException e) {  
                e.printStackTrace(); 
                returnxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><result><code>-1</code><message>"+e.getMessage()+"</message></result>";
            }  
        }
		return returnxml;
	}
	
    @SuppressWarnings("unchecked")
	public static String getReturnXml(String soapXML) throws Exception {
		String returnxml = "";
		SAXBuilder sb = new SAXBuilder();
        Reader rd = new StringReader(soapXML);
        org.jdom.Document docArg = sb.build(rd);
        Element rootArg = docArg.getRootElement();
        List lstArg = rootArg.getChildren();
        for (Iterator iter = lstArg.iterator(); iter.hasNext(); ) {
          Element el = (Element)iter.next();
          try
          {
        	if (el.getName().equalsIgnoreCase("Body")){
        		returnxml = el.getValue().toString();
        	}
          }
          catch (Exception e)
          {
        	  returnxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><result><code>-1</code><message>没有获取到返回内容 :"+e.getMessage()+"</message></result>";
          }
        }
	       return returnxml;
	   }

    /**
     * 根据输入参数拼装调用callBusiness的soap的xml串 
     * @return
     */
    private static String getCallBusinessReqXml(String username,String password,String inputxml,String jybh)
    {
        inputxml = inputxml.replaceAll("<", "&lt;");
        inputxml = inputxml.replaceAll(">", "&gt;");
        inputxml = inputxml.replaceAll("\"", "&quot;");
        String soapRequestData = "";
        soapRequestData += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
        soapRequestData += "<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">";
        soapRequestData += "  <soap:Header>";
        soapRequestData += "   <in:system xmlns:in=\"http://yinhai.com\">";
        soapRequestData += "    <userName>"+username+"</userName>";//
        soapRequestData += "    <passWord>"+password+"</passWord>";//
        soapRequestData += "    <jyztbm>028677639</jyztbm>";//交易主体编码，填写个人编号
        soapRequestData += "    <jyztyzm>3fda6b7f97a6aa82c9fbb068812d7178</jyztyzm>";//对于需要登录验证的，填写token
        soapRequestData += "    <jylsh>0</jylsh>";
        soapRequestData += "    <jyyzm>0</jyyzm>";
        soapRequestData += "    <jybh>"+jybh+"</jybh>";//交易编号
        soapRequestData += "   </in:system>";
        soapRequestData += "  </soap:Header>";
        soapRequestData += "  <soap:Body>";
        soapRequestData += "   <ns2:callBusiness xmlns:ns2=\"http://webservice.common.yinhai.com/\">";
        soapRequestData += "   <inputxml>" + inputxml + "</inputxml>";
        soapRequestData += "   </ns2:callBusiness>";
        soapRequestData += "  </soap:Body>";
        soapRequestData += "</soap:Envelope>";
        return soapRequestData;
    }
    
    
}
