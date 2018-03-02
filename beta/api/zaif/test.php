<?php
use WebSocket\Client;
class Zaif {
	const PUBLIC_BASE_URL = "https://api.zaif.jp/api/1";
	const TRADE_BASE_URL = "https://api.zaif.jp/tapi";
	const STREAMING_BASE_URL = "ws://api.zaif.jp:8888/stream";
	private $key;
	private $secret;
	private $nonce;
	public function __construct($key, $secret) {
		$this->key = $key;
		$this->secret = $secret;
		$this->nonce = time();
		$this->nonce = 1507466145;
	}
		
	public static function pub($endpoint, $prm) {
		switch ($endpoint) {
			case 'last_price':
			case 'ticker':
			case 'trades':
			case 'depth':
				break;
			default:
				throw new Exception('Argument has not been set.');
				break;
		}
		switch ($prm) {
			case 'btc_jpy':
			case 'mona_jpy':
			case 'mona_btc':
				break;
			default:
				throw new Exception('Argument has not been set.');
				break;
		}
		$url = self::PUBLIC_BASE_URL.'/'.$endpoint.'/'.$prm;
		$data = self::get($url);
		$data = json_decode( $data );
		return $data;
	}
	public function trade($method, $prms=null) {
		switch ($method) {
			case 'get_info':
			case 'get_info2':
			case 'get_personal_info':
			case 'trade_history':
			case 'active_orders':
			case 'trade' :
			case 'cancel_order' :
			case 'withdraw' :
			case 'deposit_history' :
			case 'withdraw_history' :
				break;
			default:
				throw new Exception('Argument has not been set.');
				break;
		}
		$postdata = array( "nonce" => $this->nonce++, "method" => $method );
		if( !empty( $prms ) ) {
			$postdata = array_merge( $postdata, $prms );
		}
		$postdata_query = http_build_query( $postdata );
		echo $postdata_query;
		echo "\n";
		$sign = hash_hmac( 'sha512', $postdata_query, $this->secret);
		echo $sign;
		echo "\n";
		$header = array( "Sign: {$sign}", "Key: {$this->key}", );
		print_r($postdata_query);
		echo "\n";
		print_r($header);
		$data = self::post( self::TRADE_BASE_URL, $header, $postdata_query );
		$data = json_decode( $data );
		return $data;
	}
	public static function streaming($prms, $callback) {
		$file_path = dirname(__FILE__).'/vendor/autoload.php';
		if (file_exists($file_path) && is_readable($file_path)) {
		    require_once $file_path ;
		} else {
			throw new Exception('You can not use Streaming API.You should check including libray.');
		}
		switch ($prms['currency_pair']) {
			case 'btc_jpy':
			case 'mona_jpy':
			case 'mona_btc':
				break;
			default:
				throw new Exception('Argument has not been set.');
				return 0;
				break;
		}
		$ws = self::STREAMING_BASE_URL.'?'.http_build_query($prms); 
		$client = new Client($ws);
		while(true) {
			try {
				$json = $client->receive();
				$data = json_decode($json);
				$callback($data);
			} catch (WebSocket\ConnectionException $e) {
				$clinet = new Client($ws);
			}
		}
	}	
	private static function get($url) {
		$ch = curl_init();
		$options = array(
			CURLOPT_URL => $url,
			CURLOPT_HEADER => false,
			CURLOPT_RETURNTRANSFER => true,
			CURLOPT_SSL_VERIFYPEER => false,
		);
		curl_setopt_array($ch, $options);
		$data = curl_exec($ch);
		curl_close($ch);
		return $data;
	}
	private static function post($url, $header, $postdata) {
		$ch = curl_init();
		$options = array(
			CURLOPT_URL => $url,
			CURLOPT_HEADER => false,
			CURLOPT_RETURNTRANSFER => true,
			CURLOPT_SSL_VERIFYPEER => false,
			CURLOPT_POST => true,
			CURLOPT_POSTFIELDS => $postdata,
			CURLOPT_HTTPHEADER => $header,
		);
		curl_setopt_array($ch, $options);
		$data = curl_exec($ch);
		curl_close($ch);
		return $data;
	}
}


$zaif  =  new Zaif("f8893900-b764-4cdd-9693-16c23b8a118e","049d3499-1788-4145-b033-dab66ea2feda");

//$info  =  $zaif -> trade( "get_info");
$info2  =  $zaif -> trade( "get_info2");
// 1モナ100円で15モナ売り板に出す
// $ trade_ask  =  $ zaif - > trade（ “ trade ”，
//  array（ ' currency_pair ' => ' mona_jpy '， ' action ' => ' ask '， ' price ' = > 100， ' amount ' => 15 	））;	
		  
// MONA_JPYの现在有效な注文一覧を表示する
//$ active_orders  =  $ zaif - > trade（ “ active_orders ”， array（ ' currency_pair '  =>  ' mona_jpy '））;

//出力
// var_dump( $info);
var_dump(  $info2 );

?>