package cn.aszswaz.bluetooth

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothManager
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.View.OnClickListener
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import java.util.UUID

@SuppressLint("MissingPermission")
class MainActivity : AppCompatActivity(), OnClickListener {
    companion object {
        private val TAG = MainActivity::class.simpleName
    }

    private lateinit var adapter: BluetoothAdapter;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        super.findViewById<Button>(R.id.connection).setOnClickListener(this)
        super.findViewById<Button>(R.id.start_service).setOnClickListener(this)
    }

    override fun onStart() {
        super.onStart()
        val mgr = super.getSystemService(BluetoothManager::class.java) as BluetoothManager
        this.adapter = mgr.adapter

        this.getPermissions()

        if (!this.adapter.isEnabled) {
            super.startActivity(Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE))
        }
    }

    /**
     * 通过 RFCOMM 连接蓝牙设备
     */
    override fun onClick(v: View?) {
        if (v != null) {
            when (v.id) {
                R.id.connection -> this.connectionClient()
                R.id.start_service -> this.startService()
            }
        }
    }

    /**
     * 获取蓝牙权限
     */
    private fun getPermissions() {
        val permissions = arrayListOf<String>()

        if (!this.hasPermission(Manifest.permission.BLUETOOTH))
            permissions.add(Manifest.permission.BLUETOOTH)
        if (!this.hasPermission(Manifest.permission.BLUETOOTH_CONNECT))
            permissions.add(Manifest.permission.BLUETOOTH_CONNECT)
        if (!this.hasPermission(Manifest.permission.BLUETOOTH_ADVERTISE))
            permissions.add(Manifest.permission.BLUETOOTH_ADVERTISE)
        if (!this.hasPermission(Manifest.permission.BLUETOOTH_SCAN))
            permissions.add(Manifest.permission.BLUETOOTH_SCAN)

        if (permissions.isNotEmpty())
            super.requestPermissions(permissions.toTypedArray(), 0)
    }

    private fun hasPermission(permission: String): Boolean {
        return super.checkSelfPermission(permission) == PackageManager.PERMISSION_GRANTED
    }

    private fun connectionClient() {
        val name = "rasberry-pi-4b"
        val buffer = ByteArray(8192)


        for (i in buffer.indices) {
            buffer[i] = 1
        }

        for (bondedDevice in this.adapter.bondedDevices) {
            if (bondedDevice.name == name) {
                for (uuid in bondedDevice.uuids) {
                    Log.i(TAG, uuid.toString())
                }
                val sock = bondedDevice.createRfcommSocketToServiceRecord(
                    UUID.fromString("94f39d29-7d6d-437d-973b-fba39e49d4ee")
                )
                sock.connect()
                val out = sock.outputStream
                while (true) {
                    out.write(buffer)
                }
            }
        }
    }

    private fun startService() {
        val sock = this.adapter.listenUsingRfcommWithServiceRecord(
            "aszswaz",
            UUID.fromString("93b01c88-ffe5-11ee-aa80-37147b6fabee")
        )
        val th = Thread {
            while (true) {
                val clientSock = sock.accept()
                val dev = clientSock.remoteDevice
                Log.i(TAG, "client: " + dev.name + ": " + dev.address)
            }
        }
        th.start()
        super.findViewById<Button>(R.id.start_service).isEnabled = false
    }
}