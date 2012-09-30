class CreateData < ActiveRecord::Migration
  def change
    create_table :data do |t|
      t.integer :opacity
      t.integer :number

      t.timestamps
    end
  end
end
